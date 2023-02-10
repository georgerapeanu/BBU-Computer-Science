package model.abstract_data_types.generic_dictionary;

import model.abstract_data_types.generic_dictionary.exceptions.KeyNotFoundAppException;

import java.util.*;

public class GenericDictionary<T, E> implements IGenericDictionary<T, E> {
    HashMap<T, E> data;

    public GenericDictionary() {
        data = new HashMap<>();
    }

    @Override
    public E getValue(T key) throws KeyNotFoundAppException {
        return data.get(key);
    }

    @Override
    public void setValue(T key, E value) {
        data.put(key, value);
    }

    @Override
    public List<T> getKeys() {
        return new ArrayList<>(data.keySet());
    }

    @Override
    public void removeKey(T key) throws KeyNotFoundAppException {
        data.remove(key);
    }
    @Override
    public boolean exists(T key) {
        return data.containsKey(key);
    }

    @Override
    public Map<T, E> toMap() {
        return data;
    }

    @Override
    public IGenericDictionary<T, E> copy() {
        GenericDictionary<T, E> answer = new GenericDictionary<>();
        for(T key:this.data.keySet()){
            answer.data.put(key, this.data.get(key));
        }
        return answer;
    }
}
