package model.state;

import model.abstract_data_types.generic_dictionary.GenericDictionary;
import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.abstract_data_types.generic_dictionary.exceptions.KeyNotFoundAppException;
import model.exceptions.AppException;
import model.state.exceptions.AddressOutOfBoundsAppException;
import model.values.IValue;

public class Heap implements IHeap{
    IGenericDictionary<Integer, IValue> heap;
    int firstFree;

    public Heap() {
        this.heap = new GenericDictionary<>();
        this.firstFree = 1;
    }

    @Override
    public int allocate(IValue value) {
        heap.setValue(firstFree, value);
        firstFree += 1;
        return firstFree - 1;
    }

    @Override
    public IValue read(int address) throws AddressOutOfBoundsAppException {
        try {
            return heap.getValue(address);
        } catch (KeyNotFoundAppException e) {
            throw new AddressOutOfBoundsAppException("Address " + Integer.toString(address) + " out of bounds.");
        }
    }

    @Override
    public void write(int address, IValue value) throws AddressOutOfBoundsAppException {
        if(!heap.getKeys().contains(address)) {
            throw new AddressOutOfBoundsAppException("Address " + Integer.toString(address) + " out of bounds.");
        }
        heap.setValue(address, value);
    }

    @Override
    public void deallocate(int address) throws AddressOutOfBoundsAppException {
        try {
            heap.removeKey(address);
        } catch (KeyNotFoundAppException e) {
            throw new AddressOutOfBoundsAppException("Address " + Integer.toString(address) + " out of bounds.");
        }
    }

    @Override
    public String toString(){
        StringBuilder answer = new StringBuilder("Heap:\n");
        try{
            for(int key: heap.getKeys()){
                answer.append(key).append("(").append(heap.getValue(key).getType().toString()).append(")").append(":-> ").append(heap.getValue(key).toString()).append("\n");
            }
        }catch(AppException exception){
            throw new RuntimeException(exception.getMessage());
        }
        return answer.toString();
    }
}
