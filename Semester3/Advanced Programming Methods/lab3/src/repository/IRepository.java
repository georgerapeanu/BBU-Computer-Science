package repository;

import model.state.ProgState;

public interface IRepository {
    public ProgState getCurrentProgram();
    public void addProgram(ProgState program);
}
