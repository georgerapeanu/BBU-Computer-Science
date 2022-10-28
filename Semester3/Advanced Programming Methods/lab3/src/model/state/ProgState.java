package model.state;

public class ProgState {
    IExecutionStack executionStack;
    ISymTable symTable;
    IOutput output;

    public ProgState(IExecutionStack executionStack, ISymTable symTable, IOutput output){
        this.executionStack = executionStack;
        this.symTable = symTable;
        this.output = output;
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

};
