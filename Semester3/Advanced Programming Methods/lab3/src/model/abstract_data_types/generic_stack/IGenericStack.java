package model.abstract_data_types.generic_stack;

import model.abstract_data_types.generic_stack.exceptions.StackEmptyAppException;

public interface IGenericStack<T> {
    public T pop() throws StackEmptyAppException;
    public T top() throws StackEmptyAppException;
    public void push(T elem);
    public int size();
    public boolean empty();
}
