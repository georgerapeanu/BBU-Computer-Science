package model.expressions;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.state.ProgState;
import model.state.exceptions.SymbolNotFoundAppException;
import model.values.IValue;
import model.values.types.IType;

public interface IExpression {
    public IValue evaluate(ProgState state) throws AppException;
    public String toString();

    IType typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException;

}
