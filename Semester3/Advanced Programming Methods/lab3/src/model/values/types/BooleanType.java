package model.values.types;

import model.exceptions.AppException;
import model.values.BooleanValue;
import model.values.IValue;
import model.values.exceptions.InvalidOperationAppException;

public class BooleanType implements IType{
    public BooleanType() {
        ;
    }

    @Override
    public IValue getDefaultValue() {
        return new BooleanValue(false);
    }

    @Override
    public String toString() {
        return "BooleanType";
    }
    @Override
    public boolean equals(IType other) {
        return (other instanceof BooleanType);
    }

    @Override
    public String toJavaHardCode() {
        return "new BooleanType()";
    }

    @Override
    public IType compose(String operation) throws AppException {
        switch(operation){
            case "and": return new BooleanType();
            case "or":  return new BooleanType();
            case "==":  return new BooleanType();
            case "!=":  return new BooleanType();
        }
        throw new InvalidOperationAppException("InvalidOperationAppException: Cannot compose two BooleanValue types using operation " + operation);
    }
}
