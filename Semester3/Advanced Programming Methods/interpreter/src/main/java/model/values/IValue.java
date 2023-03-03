package model.values;

import model.exceptions.AppException;
import model.values.types.IType;

public interface IValue {
    public String toString();
    public IValue compose(IValue other, String operation) throws AppException;
    IType getType();
    public boolean equals(IValue other);
    public IValue clone();
    public String toJavaHardCode();
}