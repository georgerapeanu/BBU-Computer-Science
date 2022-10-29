package model.expressions;

import model.exceptions.AppException;
import model.state.ProgState;
import model.state.exceptions.SymbolNotFoundAppException;
import model.values.IValue;
import model.values.IntegerValue;
import model.values.types.IType;

public class ConstantExpression implements IExpression {
    IValue value;

    public ConstantExpression(IValue value) {
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
