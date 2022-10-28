package controller;

import model.exceptions.AppException;
import model.statements.IStatement;

public interface IController {
    public void executeOneStep() throws AppException;
    public void executeAllSteps() throws AppException;
    public void displayCurrentState();

    void addProgram(IStatement statement);
}
