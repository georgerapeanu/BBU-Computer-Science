import wandb
import torch
import utils
import cv2
import gradio

INPUT_SHAPE = (128, 128)
model = torch.jit.load("./artifacts/scripted_model.pt")

def center_crop_square(image):
    h, w = image.shape[:2]

    # Determine the size of the square
    size = min(h, w)

    # Calculate cropping bounds
    start_h = (h - size) // 2
    start_w = (w - size) // 2
    end_h = start_h + size
    end_w = start_w + size

    # Perform cropping
    cropped_image = image[start_h:end_h, start_w:end_w]

    return cropped_image


def get_prediction_for_image(X):
    X = center_crop_square(X)
    transform = utils.transform_generator(INPUT_SHAPE)
    X, _ = transform(X, None)
    model_y = model(X.unsqueeze(dim=0))

    model_y = torch.nn.functional.interpolate(model_y, size=INPUT_SHAPE)
    model_y = model_y.squeeze(dim=0).argmax(dim=0)
    X, model_y = utils.inv_transform(X, model_y)
    return X, model_y


def gradio_fn(image):
    if image is None:
        return image

    bgr_image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
    X, output = get_prediction_for_image(bgr_image)
    output = cv2.cvtColor(output, cv2.COLOR_BGR2RGB)
    return X, output


if __name__ == '__main__':
    ui = gradio.Interface(
        fn=gradio_fn,
        inputs=gradio.Image(sources=["webcam"], streaming=True),
        outputs=["image", "image"],
        title="Image segmentation demo"
    )
    ui.launch()
