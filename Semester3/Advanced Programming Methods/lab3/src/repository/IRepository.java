package repository;

import model.state.ProgState;

import java.io.IOException;

public interface IRepository {
    public ProgState getCurrentProgram();
    public void addProgram(ProgState program);

    public void logProgramState() throws IOException;

    public void clear();
}
