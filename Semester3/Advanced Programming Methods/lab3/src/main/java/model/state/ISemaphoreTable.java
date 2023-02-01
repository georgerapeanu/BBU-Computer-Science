package model.state;

import model.exceptions.AppException;

public interface ISemaphoreTable {
    public int createSemaphore(int count) throws AppException;
    public boolean acquire(int semaphoreId, int threadId) throws AppException;
    public void release(int semaphoreId, int threadId) throws AppException;
}
