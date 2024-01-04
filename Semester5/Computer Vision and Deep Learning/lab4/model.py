import torch
import torchvision.transforms


class EncoderBlock(torch.nn.Module):
    def __init__(self, in_channels) -> None:
        super().__init__()
        self.max_pooling = torch.nn.MaxPool2d(kernel_size=2)
        self.conv1 = torch.nn.Conv2d(in_channels=in_channels, out_channels=in_channels * 2, kernel_size=3)
        self.conv2 = torch.nn.Conv2d(in_channels=in_channels * 2, out_channels=in_channels * 2, kernel_size=3)

    def forward(self, X):
        X = self.max_pooling(X)
        X = torch.nn.ReLU()(self.conv1(X))
        X = torch.nn.ReLU()(self.conv2(X))
        return X


class DecoderBlock(torch.nn.Module):
    def __init__(self, in_channels) -> None:
        super().__init__()
        self.conv2d_transpose = torch.nn.ConvTranspose2d(in_channels=in_channels, out_channels=in_channels // 2, kernel_size=2, stride=2, padding=0)
        self.batch_norm = torch.nn.BatchNorm2d(in_channels // 2)
        self.conv1 = torch.nn.Conv2d(in_channels=in_channels, out_channels=in_channels // 2, kernel_size=3)
        self.conv2 = torch.nn.Conv2d(in_channels=in_channels // 2 , out_channels=in_channels // 2, kernel_size=3)

    def forward(self, encoder_features, X):
        X = self.conv2d_transpose(X)
        X = self.batch_norm(X)
        X = torch.nn.ReLU()(X)
        encoder_features = torchvision.transforms.CenterCrop((X.shape[2], X.shape[3]))(X)
        X = torch.concat([encoder_features, X], dim=1)
        X = torch.nn.ReLU()(self.conv1(X))
        X = torch.nn.ReLU()(self.conv2(X))
        return X


class UNet(torch.nn.Module):
    def __init__(self, num_classes, num_layers = 4):
        super().__init__()
        self.conv1 = torch.nn.Conv2d(in_channels=1, out_channels=64, kernel_size=3)
        self.conv2 = torch.nn.Conv2d(in_channels=64, out_channels=64, kernel_size=3)
        self.encoders = [EncoderBlock(in_channels=64*2**i) for i in range(0, num_layers)]
        self.decoders = [DecoderBlock(in_channels=2*64*2**i) for i in range(0, num_layers)]
        self.conv3 = torch.nn.Conv2d(in_channels=64, out_channels=num_classes, kernel_size=1)

    def forward(self, X):
        X = torch.nn.ReLU()(self.conv1(X))
        X = torch.nn.ReLU()(self.conv2(X))
        outputs = [X]
        for i in range(0, len(self.encoders)):
            outputs.append(self.encoders[i].forward(outputs[i]))
        X = outputs[-1]
        for i in range(len(self.decoders) - 1, -1, -1):
            X = self.decoders[i].forward(outputs[i], X)
        X = self.conv3(X)
        return X