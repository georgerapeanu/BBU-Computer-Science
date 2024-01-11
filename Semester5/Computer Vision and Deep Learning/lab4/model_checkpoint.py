import wandb
import torch
import os


class ModelCheckpoint:
    def __init__(self, metric_name, decreasing_metric, keep = 3):
        self.best_metric_val = None
        self.metric_name = metric_name
        self.decreasing_metric = decreasing_metric
        self.keep = keep
        self.saves = []

    def __call__(self, model, epoch, metric_val):
        must_save = self.best_metric_val is None or (metric_val < self.best_metric_val if self.decreasing_metric else metric_val > self.best_metric_val)
        if must_save:
            self.best_metric_val = metric_val
            torch.save(model, f"./artifacts/model_save_{self.metric_name}_{metric_val}")
            self.saves.append((f"./artifacts/model_save_{self.metric_name}_{metric_val}", metric_val))

        while len(self.saves) > self.keep:
            os.remove(self.saves[0][0])
            self.saves = self.saves[1:]

    def __del__(self):
        for save in self.saves:
            self.write_artifact(save[0], save[1])
            os.remove(save[0])

    def write_artifact(self, model_path, metric_val):
        artifact = wandb.Artifact(f"model_{self.metric_name}", type='model', metadata={'metric': self.metric_name, 'metric_val': metric_val})
        artifact.add_file(model_path)
        wandb.run.log_artifact(artifact)
        artifact.wait()
