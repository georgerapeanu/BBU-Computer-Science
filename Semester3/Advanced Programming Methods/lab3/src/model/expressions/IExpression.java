package model.expressions;

import model.exceptions.AppException;
import model.state.ProgState;
import model.state.exceptions.SymbolNotFoundAppException;
import model.values.IValue;
import model.values.types.IType;

public interface IExpression {
    public IValue evaluate(ProgState state) throws AppException;
    public String toString();

}
