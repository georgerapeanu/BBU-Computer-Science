package model.abstract_data_types.generic_list;

import java.util.List;

public interface IGenericList<T> {
    public void addToEnd(T elem);
    List<T> getAll();
    void clear();
}
