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
            model_cpu = model.cpu()
            torch.save(model_cpu, "./artifacts/model_save")
            self.write_artifact("./artifacts/model_save", metric_val)
            os.remove("./artifacts/model_save")

        while len(self.saves) > self.keep:
            self.saves[0].wait()
            self.saves[0].delete()
            self.saves = self.saves[1:]

    def write_artifact(self, model_path, metric_val):
        artifact = wandb.Artifact(f"model_{self.metric_name}", type='model', metadata={'metric': self.metric_name, 'metric_val': metric_val})
        artifact.add_file(model_path)
        wandb.run.log_artifact(artifact)
        self.saves.append(artifact)
