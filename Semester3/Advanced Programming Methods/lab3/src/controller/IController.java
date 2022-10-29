package controller;

import model.exceptions.AppException;
import model.statements.IStatement;

public interface IController {
    public void executeOneStep() throws AppException;
    public void executeAllSteps() throws AppException;
    public void displayCurrentState();

    public void setDisplayFlag(boolean displayFlag);
    void addProgram(IStatement statement);
    public boolean getDisplayFlag();
}
