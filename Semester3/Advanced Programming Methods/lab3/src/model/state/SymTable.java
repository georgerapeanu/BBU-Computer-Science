package model.state;

import model.abstract_data_types.generic_dictionary.GenericDictionary;
import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.abstract_data_types.generic_dictionary.exceptions.KeyNotFoundAppException;
import model.exceptions.AppException;
import model.state.exceptions.SymbolAlreadyExistsAppException;
import model.state.exceptions.SymbolNotFoundAppException;
import model.values.IValue;
import model.values.types.IType;

import java.util.Map;

public class SymTable implements  ISymTable{
    IGenericDictionary<String, IValue> data;

    public SymTable() {
        data = new GenericDictionary<>();
    }

    @Override
    public void declValue(String name, IType type) throws SymbolAlreadyExistsAppException {
        if(data.exists(name)){
            throw new SymbolAlreadyExistsAppException("Symbol " + name + " already exists.");
        }
        data.setValue(name, type.getDefaultValue());
    }

    @Override
    public IValue getValue(String name) throws SymbolNotFoundAppException {
        try{
            return data.getValue(name);
        }catch(KeyNotFoundAppException exception){
            throw new SymbolNotFoundAppException("Symbol " + name + " not found.");
        }
    }

    @Override
    public void setValue(String name, IValue value) throws SymbolNotFoundAppException, KeyNotFoundAppException {
        if(!data.exists(name)){
            throw new SymbolNotFoundAppException("Symbol " + name + " not found.");
        }
        if(!data.getValue(name).getType().equals(value.getType())){
            throw new SymbolNotFoundAppException("Symbol " + name + " does not have the same type as new value.");
        }
        data.setValue(name, value);
    }

    @Override
    public String toString() {
        StringBuilder answer = new StringBuilder("SymTable:\n");
        try{
            for(String key: data.getKeys()){
                answer.append(key).append("(").append(data.getValue(key).getType().toString()).append(")").append(":-> ").append(data.getValue(key).toString()).append("\n");
            }
        }catch(AppException exception){
            throw new RuntimeException(exception.getMessage());
        }
        return answer.toString();
    }

    public Map<String, IValue> toMap(){
        return this.data.toMap();
    }
}
