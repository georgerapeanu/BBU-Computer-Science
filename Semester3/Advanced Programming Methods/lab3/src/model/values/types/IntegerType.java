package model.values.types;

import model.values.IValue;
import model.values.IntegerValue;

public class IntegerType implements IType{
    public IntegerType() {
        ;
    }

    @Override
    public IValue getDefaultValue() {
        return new IntegerValue(0);
    }

    @Override
    public String toString(){
        return "IntegerType";
    }

    @Override
    public boolean equals(IType other) {
        return (other instanceof IntegerType);
    }
}
