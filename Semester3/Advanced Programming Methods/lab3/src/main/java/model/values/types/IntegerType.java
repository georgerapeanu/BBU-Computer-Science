package model.values.types;

import model.exceptions.AppException;
import model.values.IValue;
import model.values.IntegerValue;
import model.values.exceptions.InvalidOperationAppException;

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

    @Override
    public String toJavaHardCode() {
        return "new IntegerType()";
    }

    @Override
    public IType compose(String operation) throws AppException {
        switch(operation){
            case "+":  return new IntegerType();
            case "-":  return new IntegerType();
            case "*":  return new IntegerType();
            case "/":  return new IntegerType();
            case "<":  return new BooleanType();
            case "<=": return new BooleanType();
            case "==": return new BooleanType();
            case "!=": return new BooleanType();
            case ">":  return new BooleanType();
            case ">=": return new BooleanType();
        }
        throw new InvalidOperationAppException("InvalidOperationAppException: Cannot compose two IntegerValue types using operator " + operation);
    }

}
