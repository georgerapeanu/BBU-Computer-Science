import torch.nn.functional
import wandb

from model import UNet
from lfw_dataset import LFWDataset
from torch.utils.data.dataloader import DataLoader
import numpy as np
import cv2
import pickle
from utils import transform_generator, inv_transform, eval
from model_checkpoint import ModelCheckpoint

ARTIFACTS_PATH='./artifacts'
BASE_PATH="./lfw_dataset"

def train(model, config):
    if model is None:
        model = UNet(in_channels=3, num_layers=config['NUM_LAYERS'], num_classes=3, intermediary_filters=config['INTERMEDIARY_FILTERS'])

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    model = model.to(device)

    train_dataset = LFWDataset(BASE_PATH, transforms=transform_generator(config['INPUT_SHAPE']), download=False)
    train_dataloader = DataLoader(train_dataset, batch_size=config['BATCH_SIZE'], shuffle=True)
    val_dataset = LFWDataset(BASE_PATH, transforms=transform_generator(config['INPUT_SHAPE']), download=False, split_name='validation')
    val_dataloader = DataLoader(val_dataset, batch_size=config['BATCH_SIZE'], shuffle=True)
    optim = torch.optim.Adam(model.parameters(), lr=config['LR'])
    loss_fn = torch.nn.CrossEntropyLoss()

    losses = {
        'train': [],
        'validation': []
    }

    checkpoints = {
        'val_loss': ModelCheckpoint('val_loss', True, 1),
        'mean_pixel_accuracy': ModelCheckpoint('mean_pixel_accuracy', False, 1),
        'mean_intersection_over_union': ModelCheckpoint('mean_intersection_over_union', False, 1),
        'fw_intersection_over_union': ModelCheckpoint('fw_intersection_over_union', False, 1),
    }

    for i in range(0, config['NUM_EPOCHS']):
        total_train_loss = 0
        model.train()
        for X, y in train_dataloader:
            optim.zero_grad()
            X, y = X.to(device), y.to(device)
            model_y = model(X)
            model_y = torch.nn.functional.interpolate(model_y, size=tuple(y.shape[1:]))
            loss = loss_fn(model_y, y)

            loss.backward()
            optim.step()
            total_train_loss += loss.item()

        total_val_loss = 0
        model.eval()

        columns = ["source_image", "prediction_image", "ground_truth"]
        predictons_table = wandb.Table(columns=columns)

        for X, y in val_dataloader:
            X, y = X.to(device), y.to(device)
            model_y = model(X)
            model_y = torch.nn.functional.interpolate(model_y, size=tuple(y.shape[1:]))
            loss = loss_fn(model_y, y)
            total_val_loss += loss.item()
            model_y = model_y.argmax(dim=1)
            for (source_image, prediction_image, ground_truth) in zip(X, model_y, y):
                _, model_y = inv_transform(source_image, prediction_image)
                X, y = inv_transform(source_image, ground_truth)
                predictons_table.add_data(wandb.Image(X), wandb.Image(model_y), wandb.Image(y))

        average_train_loss = total_train_loss / len(train_dataloader)
        average_val_loss = total_val_loss / len(val_dataloader)
        losses['train'].append(average_train_loss)
        losses['validation'].append(average_val_loss)
        model_eval = eval(model, val_dataloader)
        log_data = {
            'val_loss': average_val_loss,
            'train_loss': average_train_loss,
            'mean_pixel_accuracy': model_eval['mean_pixel_accuracy'],
            'mean_intersection_over_union': model_eval['mean_intersection_over_union'],
            'fw_intersection_over_union': model_eval['fw_intersection_over_union'],
            'predictons_table': predictons_table
        }
        wandb.log(log_data)
        for k in checkpoints.keys():
            checkpoints[k](model, i, log_data[k])
        print(
            f"Epoch [{i + 1}/{config['NUM_EPOCHS']}], Train Loss: {average_train_loss:.4f}, Validation Loss: {average_val_loss:.4f}")

    return model, losses


# def main():
#     try:
#         model = pickle.load(open(f"{ARTIFACTS_PATH}/model.p", "rb"))
#     except Exception:
#         model = None
#
#     model, losses = train(model)
#     pickle.dump(model, open(f"{ARTIFACTS_PATH}/model.p", "wb"))


# if __name__ == '__main__':
#     main()
