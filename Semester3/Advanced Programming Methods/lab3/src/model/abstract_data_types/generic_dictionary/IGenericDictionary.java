package model.abstract_data_types.generic_dictionary;

import model.abstract_data_types.generic_dictionary.exceptions.KeyNotFoundAppException;

import java.util.List;
import java.util.Map;

public interface IGenericDictionary<T, E> {
    public E getValue(T key)throws KeyNotFoundAppException;
    public void setValue(T key, E value);
    public List<T> getKeys();

    public void removeKey(T key) throws KeyNotFoundAppException;

    public boolean exists(T key);
    Map<T, E> toMap();
}
