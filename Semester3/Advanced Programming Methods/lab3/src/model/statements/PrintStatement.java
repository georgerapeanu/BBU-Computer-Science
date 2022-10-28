package model.statements;

import model.expressions.IExpression;
import model.state.ProgState;

public class PrintStatement implements IStatement {

    IExpression expression;

    @Override
    public void execute(ProgState progState) {
        progState.getOutput().appendToOutput(expression.evaluate().toString());
    }
}
