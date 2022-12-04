package model.statements;

import model.exceptions.AppException;
import model.state.ExecutionStack;
import model.state.IExecutionStack;
import model.state.ProgState;

public class ForkStatement implements IStatement{
    IStatement innerStatement;

    public ForkStatement(IStatement innerStatement) {
        this.innerStatement = innerStatement;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        return new ProgState(new ExecutionStack(), state.getSymTable().copy(), state.getOutput(), state.getFileTable(), state.getHeap(), innerStatement);
    }
    @Override
    public String toString(){
        return "fork(" + innerStatement.toString() + ")";
    }
}
