package controller;

import model.exceptions.AppException;
import model.statements.IStatement;

import java.io.IOException;

public interface IController {
    public void executeOneStep() throws AppException, IOException;
    public void executeAllSteps() throws AppException, IOException;
    public void displayCurrentState();

    public void setDisplayFlag(boolean displayFlag);
    void setProgram(IStatement statement) throws IOException;
    public boolean getDisplayFlag();
}
