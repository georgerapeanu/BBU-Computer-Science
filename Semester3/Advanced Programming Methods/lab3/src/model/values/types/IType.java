package model.values.types;

import model.values.IValue;

public interface IType {
    public IValue getDefaultValue();
    public String toString();
}
