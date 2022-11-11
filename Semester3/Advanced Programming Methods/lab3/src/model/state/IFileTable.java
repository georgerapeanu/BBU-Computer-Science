package model.state;

import model.exceptions.AppException;

public interface IFileTable {
    public void openFile(String name) throws AppException;
    public void closeFile(String name) throws AppException;
    public int readFile(String name) throws AppException;
    public String toString();
}
