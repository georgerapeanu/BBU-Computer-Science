import torch
import torchvision.transforms

class DoubleConv(torch.nn.Module):
    def __init__(self, in_channels, out_channels, mid_channels = None):
        super().__init__()
        if mid_channels is None:
            mid_channels = out_channels
        self.double_conv = torch.nn.Sequential(
            torch.nn.Conv2d(in_channels=in_channels, out_channels=mid_channels, kernel_size=3),
            torch.nn.BatchNorm2d(mid_channels),
            torch.nn.ReLU(inplace=True),
            torch.nn.Conv2d(in_channels=mid_channels, out_channels=out_channels, kernel_size=3),
            torch.nn.BatchNorm2d(out_channels),
            torch.nn.ReLU(inplace=True),
        )

    def forward(self, X):
        return self.double_conv(X)


class EncoderBlock(torch.nn.Module):
    def __init__(self, in_channels, out_channels) -> None:
        super().__init__()
        self.encoder = torch.nn.Sequential(
            torch.nn.MaxPool2d(kernel_size=2),
            DoubleConv(in_channels, out_channels=out_channels)
        )

    def forward(self, X):
        return self.encoder(X)


class DecoderBlock(torch.nn.Module):
    def __init__(self, in_channels, out_channels) -> None:
        super().__init__()
        self.up = torch.nn.Sequential(
            torch.nn.ConvTranspose2d(in_channels=in_channels, out_channels=in_channels // 2, kernel_size=2, stride=2, padding=0),
            torch.nn.BatchNorm2d(in_channels // 2),
            torch.nn.ReLU(inplace=True)
        )
        self.double_conv = DoubleConv(in_channels=in_channels, out_channels=out_channels, mid_channels=in_channels//2)

    def forward(self, encoder_features, X):
        X = self.up(X)
        encoder_features = torchvision.transforms.CenterCrop((X.shape[2], X.shape[3]))(encoder_features)
        X = torch.concat([encoder_features, X], dim=1)
        X = self.double_conv(X)
        return X


class UNet(torch.nn.Module):
    def __init__(self, in_channels, num_classes, num_layers = 4):
        super().__init__()
        self.in_conv = DoubleConv(in_channels=in_channels, out_channels=64, mid_channels=64)
        self.encoders = torch.nn.ModuleList([EncoderBlock(in_channels=64*2**i, out_channels=2*64*2**i) for i in range(0, num_layers)])
        self.decoders = torch.nn.ModuleList([DecoderBlock(in_channels=2*64*2**i, out_channels=64*2**i) for i in range(0, num_layers)])
        self.out_conv = torch.nn.Conv2d(in_channels=64, out_channels=num_classes, kernel_size=1)

    def forward(self, X):
        X = self.in_conv(X)
        outputs = []
        outputs.append(X)
        for i in range(0, len(self.encoders)):
            outputs.append(self.encoders[i].forward(outputs[i]))
        X = outputs[-1]
        for i in range(len(self.decoders) - 1, -1, -1):
            X = self.decoders[i].forward(outputs[i], X)
        X = self.out_conv(X)
        return X