package model.statements;

import model.state.ProgState;

public interface IStatement {
    public void execute(ProgState progState);
}
