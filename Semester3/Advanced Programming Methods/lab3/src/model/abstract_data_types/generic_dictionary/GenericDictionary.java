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
}
