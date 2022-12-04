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
    public ProgState execute(ProgState state) {
        state.getExecutionStack().push(secondStatement);
        state.getExecutionStack().push(firstStatement);
        return null;
    }

    @Override
    public String toString(){
        return firstStatement + "; " + secondStatement;
    }
}
