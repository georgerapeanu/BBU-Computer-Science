package model.state;

import controller.GarbageCollector;
import model.exceptions.AppException;
import model.statements.IStatement;

public class ProgState {

    int id;
    static int nextId = 0;
    IExecutionStack executionStack;
    ISymTable symTable;
    IOutput output;
    IFileTable fileTable;

    IHeap heap;

    public ProgState(IExecutionStack executionStack, ISymTable symTable, IOutput output, IFileTable fileTable, IHeap heap, IStatement statement){
        synchronized (ProgState.class){
            this.id = nextId;
            nextId++;
        }
        this.executionStack = executionStack;
        this.symTable = symTable;
        this.output = output;
        this.fileTable = fileTable;
        this.heap = heap;
        this.executionStack.push(statement);
    }

    public IExecutionStack getExecutionStack() {
        return executionStack;
    }

    public ISymTable getSymTable() {
        return symTable;
    }

    public IOutput getOutput() {
        return output;
    }

    public IFileTable getFileTable() {
        return fileTable;
    }

    public IHeap getHeap() {
        return heap;
    }

    public int getId() {
        return id;
    }

    public boolean isNotCompleted(){
        return this.executionStack.size() > 0;
    }

    @Override
    public String toString() {
        return "Id: " + Integer.toString(this.id) + "\n" + this.executionStack.toString().strip() + "\n" + this.symTable.toString().strip() + "\n" + this.output.toString().strip() + "\n" + this.fileTable.toString().strip() + "\n" + this.heap.toString() + "\n";
    }

    public ProgState executeOneStep() throws AppException {
        IStatement statement = executionStack.pop();
        return statement.execute(this);
    }
};
