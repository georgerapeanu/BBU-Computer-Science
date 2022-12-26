package model.statements;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.state.ProgState;
import model.state.exceptions.SymbolAlreadyExistsAppException;
import model.state.exceptions.SymbolNotFoundAppException;
import model.values.types.IType;

public interface IStatement {
    public ProgState execute(ProgState state) throws AppException;
    public String toString();
    IGenericDictionary<String, IType> typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException;
}
