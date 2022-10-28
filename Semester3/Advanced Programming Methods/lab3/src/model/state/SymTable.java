package model.state;

import model.abstract_data_types.generic_dictionary.GenericDictionary;
import model.abstract_data_types.generic_dictionary.exceptions.KeyNotFoundAppException;
import model.exceptions.AppException;
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

    @Override
    public String toDebug() {
        StringBuilder answer = new StringBuilder("SymTable:");
        try{
            for(String key: data.getKeys()){
                answer.append(key).append(":-> ").append(data.getValue(key).toString()).append("\n");
            }
        }catch(AppException exception){
            throw new RuntimeException(exception.getMessage());
        }
        return answer.toString();
    }
}
