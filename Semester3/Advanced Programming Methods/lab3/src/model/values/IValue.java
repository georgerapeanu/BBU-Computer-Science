package model.values;

import model.exceptions.AppException;

public interface IValue {
    public String toString();
    public IValue compose(IValue other, String operation) throws AppException;
}
