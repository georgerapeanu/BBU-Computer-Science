import cv2
import torch


def transform_generator(INPUT_SHAPE):
    def transform(X, y):
        if X is not None:
            #X = cv2.cvtColor(X, cv2.COLOR_BGR2GRAY)
            X = cv2.cvtColor(X, cv2.COLOR_BGR2RGB)
            #X = X.reshape(1, *X.shape)
            X = X.transpose([2, 0, 1])
            X = torch.from_numpy(X)
            X = X.to(torch.float32)
            X = torch.nn.functional.interpolate(X.view(-1, *X.shape), size=INPUT_SHAPE).view(-1, *INPUT_SHAPE)
        if y is not None:
            y = y.transpose([2, 0, 1])
            y = torch.from_numpy(y)
            y = y.to(torch.float32)
            y = torch.nn.functional.interpolate(y.view(1, *y.shape), size=INPUT_SHAPE).view(-1, *INPUT_SHAPE)
            y = torch.argmax(y, dim=0)
        return X, y

    return transform


def inv_transform(X, y):
    if y is not None:
        y = torch.nn.functional.one_hot(y, num_classes=3) * torch.tensor(255)
        y = y.to(torch.uint8)
        y = y.cpu().numpy()
    if X is not None:
        X = X.to(torch.uint8)
        X = X.cpu().numpy()
        X = X.transpose([1, 2, 0])
    return X, y

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

def get_helpers(model, dl):
    model.eval()
    total_belonging = None
    for X, y in dl:
        X, y = X.to(device), y.to(device)
        model_ys = model(X)
        model_ys = torch.nn.functional.interpolate(model_ys, size=tuple(y.shape[1:]))
        model_ys = model_ys.argmax(dim=1)
        model_ys = torch.nn.functional.one_hot(model_ys, num_classes=3)
        test_ys = torch.nn.functional.one_hot(y, num_classes=3)

        model_ys = model_ys.cpu()
        test_ys = test_ys.cpu()

        model_ys_shape_list = list(model_ys.shape)
        model_ys_shape_list.insert(-1, 1)
        # (test_index, row, col, ground_class, model_class)
        belonging_data = test_ys.view(*test_ys.shape, 1) @ model_ys.view(model_ys_shape_list)
        belonging_data = belonging_data.sum(dim=1)
        belonging_data = belonging_data.sum(dim=1)
        belonging_data = belonging_data.sum(dim=0)
        if total_belonging is None:
            total_belonging = belonging_data.cpu()
        else:
            total_belonging += belonging_data.cpu()

    return total_belonging


def eval(model, ds):
    model.eval()
    belongind_data = get_helpers(model, ds)
    ground_truth_data = torch.sum(belongind_data, dim=1)
    correctly_labeled_data = torch.diagonal(belongind_data)

    mean_pixel_accuracy = torch.mean(correctly_labeled_data / ground_truth_data)
    mean_intersection_over_union = torch.mean(
        correctly_labeled_data / (ground_truth_data - correctly_labeled_data + torch.sum(belongind_data, dim=0)))
    fw_intersection_over_union = torch.sum(ground_truth_data * (correctly_labeled_data / (
            ground_truth_data - correctly_labeled_data + torch.sum(belongind_data, dim=0)))) / torch.sum(
        ground_truth_data)
    return {
        'mean_pixel_accuracy': mean_pixel_accuracy,
        'mean_intersection_over_union': mean_intersection_over_union,
        'fw_intersection_over_union': fw_intersection_over_union
    }
