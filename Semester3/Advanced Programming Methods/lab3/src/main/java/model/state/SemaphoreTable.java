package model.state;

import javafx.util.Pair;
import model.abstract_data_types.generic_dictionary.GenericDictionary;
import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.abstract_data_types.generic_list.GenericList;
import model.abstract_data_types.generic_list.IGenericList;
import model.exceptions.AppException;
import model.state.exceptions.SemaphoreAppException;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.ReentrantLock;

public class SemaphoreTable implements ISemaphoreTable{
    private static int nextId = 0;
    ReentrantLock lock;
    IGenericDictionary<Integer, Pair<Integer, IGenericList<Integer>>> semaphores;

    public SemaphoreTable() {
        this.lock = new ReentrantLock();
        this.semaphores = new GenericDictionary<>();
    }

    @Override
    public int createSemaphore(int count) throws SemaphoreAppException {
        if(count < 0){
            throw new SemaphoreAppException("Non negative count expected for semaphore");
        }
        int id;
        lock.lock();
        semaphores.setValue(nextId, new Pair<>(count, new GenericList<>()));
        id = nextId;
        nextId++;
        lock.unlock();
        return id;
    }

    @Override
    public boolean acquire(int semaphoreId, int threadId) throws AppException{
        lock.lock();
        try {
            if (!semaphores.exists(semaphoreId)) {
                throw new SemaphoreAppException("Semaphore doesn't exist");
            }
            Pair<Integer, IGenericList<Integer>> semaphore = semaphores.getValue(semaphoreId);
            if(semaphore.getKey() > semaphore.getValue().getAll().size()){
                if(!semaphore.getValue().getAll().contains(threadId)){
                    semaphore.getValue().addToEnd(threadId);
                }
                return true;
            } else {
                return false;
            }
        } finally{
            lock.unlock();
        }
    }

    @Override
    public void release(int semaphoreId, int threadId) throws AppException{
        lock.lock();
        try {
            if (!semaphores.exists(semaphoreId)) {
                throw new SemaphoreAppException("Semaphore doesn't exist");
            }
            Pair<Integer, IGenericList<Integer>> semaphore = semaphores.getValue(semaphoreId);

            if(semaphore.getValue().getAll().contains(threadId)){
                semaphore.getValue().remove(threadId);
            }
        } finally{
            lock.unlock();
        }
    }

    @Override
    public List<Pair<Pair<Integer, Integer>, IGenericList<Integer>>> getSemaphoreDecitionaryAsList() {
        this.lock.lock();
        List<Pair<Pair<Integer, Integer>, IGenericList<Integer> > > answer = new ArrayList<>();
        this.semaphores.toMap().forEach((x, y) -> {
            answer.add(new Pair<>(new Pair<>(x, y.getKey()), y.getValue()));
        });
        this.lock.unlock();
        return answer;
    }
}
