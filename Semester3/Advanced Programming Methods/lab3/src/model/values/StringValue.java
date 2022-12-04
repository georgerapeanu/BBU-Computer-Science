package model.values;

import model.exceptions.AppException;
import model.values.exceptions.InvalidOperationAppException;
import model.values.types.BooleanType;
import model.values.types.IType;
import model.values.types.StringType;

import java.util.Objects;

public class StringValue implements IValue{
    String value;
    public StringValue() {
        this.value = "";
    }

    public StringValue(String value) {
        this.value = value;
    }

    private StringValue add(StringValue other) {
        return new StringValue(this.value + other.getValue());
    }

    private BooleanValue lessThan(StringValue other) {
        return new BooleanValue(this.value.compareTo(other.value) < 0);
    }

    private BooleanValue lessThanEqual(StringValue other) {
        return new BooleanValue(this.value.compareTo(other.value) <= 0);
    }

    private BooleanValue greaterThan(StringValue other) {
        return new BooleanValue(this.value.compareTo(other.value) > 0);
    }

    private BooleanValue greaterThanEqual(StringValue other) {
        return new BooleanValue(this.value.compareTo(other.value) >= 0);
    }

    private BooleanValue equal(StringValue other) {
        return new BooleanValue(this.equals(other));
    }

    private BooleanValue notEqual(StringValue other) {
        return new BooleanValue(!this.equals(other));
    }

    @Override
    public String toString(){
        return '"' + this.value + '"';
    }

    @Override
    public IValue compose(IValue other, String operation) throws AppException {
        if(!(other.getType().equals(this.getType()))) {
            throw new InvalidOperationAppException("InvalidOperationAppException: Cannot compose two different types using operator " + operation);
        }
        switch(operation){
            case "+": return this.add((StringValue)other);
            case "<":   return this.lessThan((StringValue) other);
            case "<=":  return this.lessThanEqual((StringValue) other);
            case "==":  return this.equal((StringValue) other);
            case "!=":  return this.notEqual((StringValue) other);
            case ">":   return this.greaterThan((StringValue)other);
            case ">=":  return this.greaterThanEqual((StringValue)other);
        }
        throw new InvalidOperationAppException("InvalidOperationAppException: Cannot compose two StringValue types using operation " + operation);
    }

    @Override
    public IType getType() {
        return new StringType();
    }

    @Override
    public boolean equals(IValue other){
        if(other.getType() instanceof StringType){
            return Objects.equals(this.getValue(), ((StringValue) other).getValue());
        }
        return false;
    }

    @Override
    public IValue clone() {
        return new StringValue(this.value);
    }

    public String getValue() {
        return this.value;
    }
}
