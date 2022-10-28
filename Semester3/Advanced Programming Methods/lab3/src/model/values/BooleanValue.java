package model.values;

import model.values.exceptions.DivisionOverflowAppException;
import model.values.exceptions.InvalidOperationAppException;

public class BooleanValue implements IValue{
    boolean value;

    public BooleanValue(){
        this.value = false;
    }

    public BooleanValue(boolean value){
        this.value = value;
    }

    public BooleanValue and(BooleanValue other) {
        return new BooleanValue(this.value & other.value);
    }

    public BooleanValue or(BooleanValue other) {
        return new BooleanValue(this.value | other.value);
    }

    @Override
    public String toString(){
        return Boolean.toString(value);
    }

    @Override
    public IValue compose(IValue other, String operation) throws InvalidOperationAppException {
        if(!(other instanceof BooleanValue)) {
            throw new InvalidOperationAppException("InvalidOperationAppException: Cannot compose two different types using operation " + operation);
        }
        switch(operation){
            case "and": return this.and((BooleanValue) other);
            case "or": return this.or((BooleanValue) other);
        }
        throw new InvalidOperationAppException("InvalidOperationAppException: Cannot compose two different types using operation " + operation);
    }
}
