package repository;

import model.state.ProgState;

import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository{
    List<ProgState> programs;
    public Repository() {
        programs = new ArrayList<>();
    }

    @Override
    public ProgState getCurrentProgram() {
        return programs.get(0);
    }

    @Override
    public void addProgram(ProgState program) {
        programs.add(program);
    }
}
