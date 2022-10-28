package model.state;

import model.abstract_data_types.generic_dictionary.GenericDictionary;
import model.abstract_data_types.generic_dictionary.exceptions.KeyNotFoundAppException;
import model.values.IValue;

public class SymTable implements  ISymTable{
    GenericDictionary<String, IValue> data;

    public SymTable() {
        data = new GenericDictionary<>();
    }

    @Override
    public IValue getValue(String name) throws KeyNotFoundAppException {
        return data.getValue(name);
    }

    @Override
    public void setValue(String name, IValue value) {
        data.setValue(name, value);
    }
}
