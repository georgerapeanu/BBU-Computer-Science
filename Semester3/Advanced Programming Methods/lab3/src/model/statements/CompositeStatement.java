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
    public void execute(ProgState state) {
        state.getExecutionStack().push(secondStatement);
        state.getExecutionStack().push(firstStatement);
    }

    @Override
    public String toString(){
        return firstStatement + "; " + secondStatement;
    }
}
