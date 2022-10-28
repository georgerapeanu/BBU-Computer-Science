package controller;

import model.exceptions.AppException;

public interface IController {
    public void executeOneStep() throws AppException;
    public void executeAllSteps() throws AppException;
    public void displayCurrentState();
}
