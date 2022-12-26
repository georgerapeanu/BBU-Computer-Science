package model.expressions;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
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

    @Override
    public IType typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException {
        return typeDictionary.getValue(name);
    }

    @Override
    public String toJavaHardCode() {
        return "new VariableExpression(" + "\"" + name + "\"" + ")";
    }

}
