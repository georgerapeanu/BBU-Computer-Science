package model.expressions;

import model.exceptions.AppException;
import model.state.ProgState;
import model.values.IValue;
import model.values.IntegerValue;

public class ConstantExpression implements IExpression {
    IntegerValue value;

    public ConstantExpression(IntegerValue value) {
        this.value = value;
    }

    @Override
    public IValue evaluate(ProgState state) throws AppException {
        return value;
    }

    @Override
    public String toString(){
        return value.toString();
    }
};
