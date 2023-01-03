package model.values.types;

import model.exceptions.AppException;
import model.values.IValue;
import model.values.StringValue;
import model.values.exceptions.InvalidOperationAppException;

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

    @Override
    public String toJavaHardCode() {
        return "new StringType()";
    }
    @Override
    public IType compose(String operation) throws AppException {
        switch(operation){
            case "+":   return new StringType();
            case "<":   return new BooleanType();
            case "<=":  return new BooleanType();
            case "==":  return new BooleanType();
            case "!=":  return new BooleanType();
            case ">":   return new BooleanType();
            case ">=":  return new BooleanType();
        }
        throw new InvalidOperationAppException("InvalidOperationAppException: Cannot compose two StringValue types using operation " + operation);
    }

}
