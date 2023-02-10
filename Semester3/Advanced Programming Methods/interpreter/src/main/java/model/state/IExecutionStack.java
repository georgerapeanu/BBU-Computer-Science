package model.state;

import model.abstract_data_types.generic_stack.exceptions.StackEmptyAppException;
import model.statements.IStatement;

import java.util.List;

public interface IExecutionStack {
    public IStatement pop() throws StackEmptyAppException;
    public void push(IStatement statement);
    public boolean empty();
    public int size();
    public String toString();
    public List<IStatement> toList();
}
