package model.statements;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.state.ProgState;
import model.values.types.IType;

public class NoOperationStatement implements IStatement{
    public NoOperationStatement() {
        ;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        return null;
    }

    @Override
    public String toString(){
        return "NOP";
    }

    @Override
    public IGenericDictionary<String, IType> typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException {
        return typeDictionary;
    }
}
