package model.state;

import model.statements.IStatement;

public class ProgState {
    IExecutionStack executionStack;
    ISymTable symTable;
    IOutput output;

    public ProgState(IExecutionStack executionStack, ISymTable symTable, IOutput output, IStatement statement){
        this.executionStack = executionStack;
        this.symTable = symTable;
        this.output = output;
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

    public String toDebug() {
        return this.executionStack.toDebug().strip() + "\n" + this.symTable.toDebug().strip() + "\n" + this.output.toDebug().strip();
    }
};
