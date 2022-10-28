package model.state;

import model.abstract_data_types.generic_stack.IGenericStack;
import model.abstract_data_types.generic_stack.exceptions.StackEmptyAppException;
import model.statements.IStatement;

public class ExecutionStack implements IExecutionStack {
    IGenericStack<IStatement> stack;

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
}
