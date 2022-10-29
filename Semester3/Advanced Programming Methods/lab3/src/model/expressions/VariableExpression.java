package model.expressions;

import model.exceptions.AppException;
import model.state.ProgState;
import model.state.exceptions.SymbolNotFoundAppException;
import model.values.IValue;
import model.values.types.IType;

public class VariableExpression implements IExpression{
    String name;

    public VariableExpression(String name) {
        this.name = name;
    }

    @Override
    public IValue evaluate(ProgState state) throws AppException {
        return state.getSymTable().getValue(this.name);
    }

    @Override
    public String toString(){
        return name;
    }

}
