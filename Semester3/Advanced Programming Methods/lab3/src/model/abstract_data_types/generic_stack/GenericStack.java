package model.abstract_data_types.generic_stack;

import model.abstract_data_types.generic_stack.exceptions.StackEmptyAppException;

import java.util.Stack;

public class GenericStack<T> implements IGenericStack<T> {
    Stack<T> stack;

    public GenericStack(){
        this.stack = new Stack<>();
    };

    @Override
    public T pop() throws StackEmptyAppException {
        if(stack.empty()){
            throw new StackEmptyAppException("Cannot pop from an empty stack");
        }
        return stack.pop();
    }

    @Override
    public T top() throws StackEmptyAppException{
        if(stack.empty()){
            throw new StackEmptyAppException("Cannot pop from an empty stack");
        }
        return stack.peek();
    }

    @Override
    public void push(T elem) {
        stack.push(elem);
    }

    @Override
    public int size() {
        return stack.size();
    }

    @Override
    public boolean empty() {
        return stack.empty();
    }
}
