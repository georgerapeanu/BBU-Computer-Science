package model.values;

import model.values.exceptions.DivisionOverflowAppException;
import model.values.exceptions.InvalidOperationAppException;

public class IntegerValue implements  IValue{
    int value;
    public IntegerValue(){
        this.value = 0;
    }

    public IntegerValue(int value){
        this.value = value;
    }

    public IntegerValue add(IntegerValue other) {
        return new IntegerValue(this.value + other.value);
    }

    public IntegerValue subtract(IntegerValue other) {
        return new IntegerValue(this.value - other.value);
    }

    public IntegerValue multiply(IntegerValue other) {
        return new IntegerValue(this.value * other.value);
    }

    public IntegerValue divide(IntegerValue other) throws DivisionOverflowAppException {
        if(other.value == 0){
            throw new DivisionOverflowAppException("DivisionOverflowAppException: Cannot divide by 0");
        }
        return new IntegerValue(this.value / other.value);
    }

    @Override
    public String toString() {
        return Integer.toString(value);
    }

    @Override
    public IValue compose(IValue other, String operation) throws InvalidOperationAppException, DivisionOverflowAppException{
        if(!(other instanceof IntegerValue)) {
            throw new InvalidOperationAppException("InvalidOperationAppException: Cannot compose two different types using operator " + operation);
        }
        switch(operation){
            case "+": return this.add((IntegerValue)other);
            case "-": return this.subtract((IntegerValue)other);
            case "*": return this.multiply((IntegerValue)other);
            case "/": return this.divide((IntegerValue)other);
        }
        throw new InvalidOperationAppException("InvalidOperationAppException: Cannot compose two different types using operator " + operation);
    }
}
