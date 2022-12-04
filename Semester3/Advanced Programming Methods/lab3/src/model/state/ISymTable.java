package model.state;

import model.exceptions.AppException;
import model.values.IValue;
import model.values.types.IType;

import java.util.Map;

public interface ISymTable {

    public void declValue(String name, IType type) throws AppException;
    public IValue getValue(String name) throws AppException;
    public void setValue(String name, IValue value) throws AppException;
    public String toString();
    public ISymTable copy() throws AppException;
    public Map<String, IValue> toMap();
}
