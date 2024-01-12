import wandb
import torch
import utils
import cv2
import gradio

INPUT_SHAPE = (64, 64)
model = torch.jit.load("./artifacts/scripted_model.pt")


def get_prediction_for_image(X):
    transform = utils.transform_generator(INPUT_SHAPE)
    X, _ = transform(X, None)
    model_y = model(X.unsqueeze(dim=0))

    model_y = torch.nn.functional.interpolate(model_y, size=INPUT_SHAPE)
    model_y = model_y.squeeze(dim=0).argmax(dim=0)
    _, model_y = utils.inv_transform(None, model_y)
    return model_y


def gradio_fn(image):
    if image is None:
        return image

    bgr_image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
    output = get_prediction_for_image(bgr_image)
    return output


if __name__ == '__main__':
    ui = gradio.Interface(
        fn=gradio_fn,
        inputs=gradio.Image(sources=["webcam"], streaming=True),
        outputs="image",
        title="Image segmentation demo"
    )
    ui.launch()
