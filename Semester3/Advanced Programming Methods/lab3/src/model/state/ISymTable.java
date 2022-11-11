package model.state;

import model.state.exceptions.SymbolAlreadyExistsAppException;
import model.state.exceptions.SymbolNotFoundAppException;
import model.values.IValue;
import model.values.types.IType;

public interface ISymTable {

    public void declValue(String name, IType type) throws SymbolAlreadyExistsAppException;
    public IValue getValue(String name) throws SymbolNotFoundAppException;
    public void setValue(String name, IValue value) throws SymbolNotFoundAppException;
    public String toString();
}