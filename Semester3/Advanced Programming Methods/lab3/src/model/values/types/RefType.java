package model.values.types;

import model.exceptions.AppException;
import model.values.IValue;
import model.values.RefValue;
import model.values.exceptions.InvalidOperationAppException;

public class RefType implements IType{
    IType inner;
    public RefType(IType inner) {
        this.inner = inner;
    }

    @Override
    public IValue getDefaultValue() {
        return new RefValue(0, inner);
    }

    @Override
    public String toString() {
        return "RefType " + this.inner.toString();
    }

    @Override
    public boolean equals(IType other) {
        return (other instanceof RefType) && ((RefType)other).inner != null && ((RefType) other).inner.equals(this.inner);
    }

    @Override
    public String toJavaHardCode() {
        return "new RefType(" + this.inner.toJavaHardCode() + ")";
    }

    @Override
    public IType compose(String operation) throws AppException {
        throw new InvalidOperationAppException("InvalidOperationAppException: Cannot compose two RefValue types using operator " + operation);
    }
}
