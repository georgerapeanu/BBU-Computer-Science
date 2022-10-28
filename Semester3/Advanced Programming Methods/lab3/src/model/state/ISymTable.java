package model.state;

import model.abstract_data_types.generic_dictionary.exceptions.KeyNotFoundAppException;
import model.values.IValue;

public interface ISymTable {
    public IValue getValue(String name) throws KeyNotFoundAppException;
    public void setValue(String name, IValue value);
}
