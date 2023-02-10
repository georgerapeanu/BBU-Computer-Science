package controller;

import model.exceptions.AppException;
import model.state.ProgState;
import model.statements.IStatement;

import java.io.IOException;
import java.util.List;

public interface IController {
    public void executeOneStep() throws AppException;
    public void executeAllSteps() throws AppException;
    public void displayCurrentState() throws AppException;
    public void removeCompletedPrograms();
    public void setDisplayFlag(boolean displayFlag);
    void setProgram(IStatement statement) throws AppException;
    public boolean getDisplayFlag();
    public List<ProgState> getProgStates();
}
