package model.state;

import model.abstract_data_types.generic_dictionary.exceptions.KeyNotFoundAppException;
import model.exceptions.AppException;
import model.state.exceptions.SymbolAlreadyExistsAppException;
import model.state.exceptions.SymbolNotFoundAppException;
import model.values.IValue;
import model.values.types.IType;

public interface ISymTable {

    public void declValue(String name, IType type) throws AppException;
    public IValue getValue(String name) throws AppException;
    public void setValue(String name, IValue value) throws AppException;
    public String toString();
}
