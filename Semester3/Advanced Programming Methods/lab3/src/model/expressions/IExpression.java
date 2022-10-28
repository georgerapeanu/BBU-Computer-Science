package model.expressions;

import model.exceptions.AppException;
import model.state.ProgState;
import model.values.IValue;

public interface IExpression {
    public IValue evaluate(ProgState state) throws AppException;
    public String toString();
}
