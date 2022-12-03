package model.values.types;

import model.values.IValue;
import model.values.StringValue;

public class StringType implements IType{
    public StringType() {
        ;
    }

    @Override
    public IValue getDefaultValue() {
        return new StringValue("");
    }

    @Override
    public String toString() {
        return "StringType";
    }

    @Override
    public boolean equals(IType other) {
        return (other instanceof StringType);
    }
}
