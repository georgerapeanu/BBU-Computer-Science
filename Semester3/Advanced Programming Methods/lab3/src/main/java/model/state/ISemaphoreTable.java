package model.state;

import javafx.util.Pair;
import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.abstract_data_types.generic_list.IGenericList;
import model.exceptions.AppException;

import java.util.List;

public interface ISemaphoreTable {
    public int createSemaphore(int count) throws AppException;
    public boolean acquire(int semaphoreId, int threadId) throws AppException;
    public void release(int semaphoreId, int threadId) throws AppException;
    public List<Pair<Pair<Integer, Integer>, IGenericList<Integer>>> getSemaphoreDecitionaryAsList();
}
