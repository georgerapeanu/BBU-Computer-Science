package model.abstract_data_types.generic_list;

import java.util.ArrayList;
import java.util.List;

public class GenericList<T> implements IGenericList<T>{
    List<T> data;

    public GenericList() {
        data = new ArrayList<>();
    }

    public GenericList(List<T> data) {
        this.data = data;
    }

    @Override
    public void addToEnd(T elem) {
        data.add(elem);
    }

    @Override
    public List<T> getAll() {
        return data;
    }

    @Override
    public void clear() {
        this.data.clear();
    }
}
