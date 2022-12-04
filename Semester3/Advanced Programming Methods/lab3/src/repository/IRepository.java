package repository;

import model.exceptions.AppException;
import model.state.ProgState;

import java.io.IOException;
import java.util.List;

public interface IRepository {
    public List<ProgState> getProgramsList();
    public void setProgramsList(List<ProgState> programs);
    public void addProgram(ProgState program);

    public void logProgramState(ProgState program);

    public void clear();
}
