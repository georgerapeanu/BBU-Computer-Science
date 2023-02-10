package model.values;

import model.exceptions.AppException;
import model.values.exceptions.DivisionOverflowAppException;
import model.values.exceptions.InvalidOperationAppException;
import model.values.types.BooleanType;
import model.values.types.IType;
import model.values.types.IntegerType;

public class IntegerValue implements  IValue{
    int value;
    public IntegerValue(){
        this.value = 0;
    }

    public IntegerValue(int value){
        this.value = value;
    }

    private IntegerValue add(IntegerValue other) {
        return new IntegerValue(this.value + other.value);
    }

    private IntegerValue subtract(IntegerValue other) {
        return new IntegerValue(this.value - other.value);
    }

    private IntegerValue multiply(IntegerValue other) {
        return new IntegerValue(this.value * other.value);
    }

    private IntegerValue divide(IntegerValue other) throws DivisionOverflowAppException {
        if(other.value == 0){
            throw new DivisionOverflowAppException("DivisionOverflowAppException: Cannot divide by 0");
        }
        return new IntegerValue(this.value / other.value);
    }

    private BooleanValue lessThan(IntegerValue other) {
        return new BooleanValue(this.value < other.value);
    }

    private BooleanValue lessThanEqual(IntegerValue other) {
        return new BooleanValue(this.value <= other.value);
    }

    private BooleanValue greaterThan(IntegerValue other) {
        return new BooleanValue(this.value > other.value);
    }

    private BooleanValue greaterThanEqual(IntegerValue other) {
        return new BooleanValue(this.value >= other.value);
    }

    private BooleanValue equal(IntegerValue other) {
        return new BooleanValue(this.equals(other));
    }

    private BooleanValue notEqual(IntegerValue other) {
        return new BooleanValue(!this.equals(other));
    }

    @Override
    public String toString() {
        return Integer.toString(value);
    }

    @Override
    public IValue compose(IValue other, String operation) throws InvalidOperationAppException, DivisionOverflowAppException{
        if(!(other.getType().equals(this.getType()))) {
            throw new InvalidOperationAppException("InvalidOperationAppException: Cannot compose two different types using operator " + operation);
        }
        switch(operation){
            case "+": return this.add((IntegerValue)other);
            case "-": return this.subtract((IntegerValue)other);
            case "*": return this.multiply((IntegerValue)other);
            case "/": return this.divide((IntegerValue)other);
            case "<":   return this.lessThan((IntegerValue) other);
            case "<=":  return this.lessThanEqual((IntegerValue) other);
            case "==":  return this.equal((IntegerValue) other);
            case "!=":  return this.notEqual((IntegerValue) other);
            case ">":   return this.greaterThan((IntegerValue)other);
            case ">=":  return this.greaterThanEqual((IntegerValue)other);
        }
        throw new InvalidOperationAppException("InvalidOperationAppException: Cannot compose two IntegerValue types using operator " + operation);
    }

    @Override
    public IType getType() {
        return new IntegerType();
    }

    @Override
    public boolean equals(IValue other){
        if(other.getType() instanceof IntegerType){
            return this.getValue() == ((IntegerValue)other).getValue();
        }
        return false;
    }

    @Override
    public IValue clone() {
        return new IntegerValue(this.value);
    }

    @Override
    public String toJavaHardCode() {
        return "new IntegerValue(" + String.valueOf(this.value) + ")";
    }

    public int getValue() {
        return this.value;
    }
}
