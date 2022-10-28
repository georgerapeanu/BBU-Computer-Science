package model.abstract_data_types.generic_dictionary;

import model.abstract_data_types.generic_dictionary.exceptions.KeyNotFoundAppException;

public interface IGenericDictionary<T, E> {
    public E getValue(T key)throws KeyNotFoundAppException;
    public void setValue(T key, E value);
}
