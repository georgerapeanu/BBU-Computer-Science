package model.state;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.expressions.IExpression;
import model.state.exceptions.AddressOutOfBoundsAppException;
import model.values.IValue;

public interface IHeap {
    public int allocate(IValue value);
    public IValue read(int address) throws AddressOutOfBoundsAppException;
    public void write(int address, IValue value) throws AddressOutOfBoundsAppException;
    public void deallocate(int address) throws AddressOutOfBoundsAppException;
}
