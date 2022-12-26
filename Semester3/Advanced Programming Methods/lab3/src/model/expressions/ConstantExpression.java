package model.expressions;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
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

    @Override
    public IType typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException {
        return value.getType();
    }

    @Override
    public String toJavaHardCode() {
        return "new ConstantExpression(" + value.toJavaHardCode() + ")";
    }

};
