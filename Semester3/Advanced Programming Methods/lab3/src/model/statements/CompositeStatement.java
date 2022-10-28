package model.statements;

import model.state.ProgState;

public class CompositeStatement implements IStatement{
    IStatement firstStatement;
    IStatement secondStatement;

    public CompositeStatement(IStatement firstStatement, IStatement secondStatement) {
        this.firstStatement = firstStatement;
        this.secondStatement = secondStatement;
    }

    @Override
    public void execute(ProgState progState) {
        progState.getExecutionStack().push(secondStatement);
        progState.getExecutionStack().push(firstStatement);
    }
}
