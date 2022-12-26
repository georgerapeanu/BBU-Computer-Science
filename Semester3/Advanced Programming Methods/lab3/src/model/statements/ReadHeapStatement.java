package model.statements;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ProgState;
import model.values.IValue;
import model.values.types.IType;
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

    @Override
    public IGenericDictionary<String, IType> typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException {
        expr.typecheck(typeDictionary);
        return typeDictionary;
    }
}
