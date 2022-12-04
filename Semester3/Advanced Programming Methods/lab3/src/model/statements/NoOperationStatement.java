package model.statements;

import model.exceptions.AppException;
import model.state.ProgState;

public class NoOperationStatement implements IStatement{
    public NoOperationStatement() {
        ;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        return null;
    }

    @Override
    public String toString(){
        return "NOP";
    }
}
