package model.statements;

import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ProgState;

public class PrintStatement implements IStatement {

    IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        state.getOutput().appendToOutput(expression.evaluate(state).toString());
        return null;
    }

    @Override
    public String toString(){
        return "print(" + expression.toString() + ")";
    }
}
