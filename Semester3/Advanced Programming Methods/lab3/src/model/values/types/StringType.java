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
}
