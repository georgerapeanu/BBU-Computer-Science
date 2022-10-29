package model.statements;

import model.exceptions.AppException;
import model.state.ProgState;

public class NoOperationStatement implements IStatement{
    public NoOperationStatement() {
        ;
    }

    @Override
    public void execute(ProgState state) throws AppException {
        ;
    }

    @Override
    public String toString(){
        return "NOP";
    }
}
