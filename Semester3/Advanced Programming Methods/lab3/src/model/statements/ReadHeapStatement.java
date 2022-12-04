package model.statements;

import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ProgState;
import model.values.IValue;
import model.values.types.RefType;

public class ReadHeapStatement implements IStatement{
    IExpression expr;

    public ReadHeapStatement(IExpression expr) {
        this.expr = expr;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        expr.evaluate(state);
        return null;
    }

    @Override
    public String toString() {
        return expr.toString();
    }
}
