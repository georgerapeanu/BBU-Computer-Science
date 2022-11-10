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

    public StringValue add(StringValue other) {
        return new StringValue(this.value + other.getValue());
    }

    @Override
    public String toString(){
        return this.value;
    }

    @Override
    public IValue compose(IValue other, String operation) throws AppException {
        if(!(other.getType() instanceof StringType)) {
            throw new InvalidOperationAppException("InvalidOperationAppException: Cannot compose two different types using operator " + operation);
        }
        switch(operation){
            case "+": return this.add((StringValue)other);
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

    public String getValue() {
        return this.value;
    }
}
