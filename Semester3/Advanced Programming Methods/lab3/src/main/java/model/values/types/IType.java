package model.values.types;

import model.exceptions.AppException;
import model.values.IValue;

public interface IType {
    public IValue getDefaultValue();
    public String toString();
    public boolean equals(IType other);
    String toJavaHardCode();
    public IType compose(String operation) throws AppException;
}
