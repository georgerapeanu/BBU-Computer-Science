package repository;

import model.exceptions.AppException;
import model.state.ProgState;

import java.io.IOException;

public interface IRepository {
    public ProgState getCurrentProgram() throws AppException;
    public void addProgram(ProgState program);

    public void logProgramState();

    public void clear();
}
