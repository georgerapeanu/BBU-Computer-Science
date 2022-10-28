package model.statements;

import model.expressions.IExpression;
import model.state.ProgState;

public class AssignmentStatement implements  IStatement{
    String variableName;
    IExpression expression;

    @Override
    public void execute(ProgState progState) {
        progState.getSymTable().setValue(variableName, expression.evaluate());
    }
}
