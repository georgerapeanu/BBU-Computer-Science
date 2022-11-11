package model.state;

import model.abstract_data_types.generic_stack.GenericStack;
import model.abstract_data_types.generic_stack.IGenericStack;
import model.abstract_data_types.generic_stack.exceptions.StackEmptyAppException;
import model.exceptions.AppException;
import model.statements.IStatement;

public class ExecutionStack implements IExecutionStack {
    IGenericStack<IStatement> stack;

    public ExecutionStack() {
        this.stack = new GenericStack<>();
    }

    @Override
    public IStatement pop() throws StackEmptyAppException {
        return stack.pop();
    }

    @Override
    public void push(IStatement statement) {
        stack.push(statement);
    }

    @Override
    public boolean empty() {
        return stack.empty();
    }

    @Override
    public int size() {
        return stack.size();
    }

    @Override
    public String toString() {
        StringBuilder answer = new StringBuilder("Execution stack:\n");
        IGenericStack<IStatement> tmpStack = new GenericStack<>();
        try{
            while(!stack.empty()){
                tmpStack.push(stack.pop());
                answer.append(tmpStack.top().toString()).append('\n');
            }
            while(!tmpStack.empty()){
                stack.push(tmpStack.pop());
            }
        }catch (AppException exception){
            throw new RuntimeException(exception.getMessage());
        }
        return answer.toString();
    }
}
