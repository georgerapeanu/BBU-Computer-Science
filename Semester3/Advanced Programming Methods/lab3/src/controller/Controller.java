package controller;

import model.abstract_data_types.generic_stack.exceptions.StackEmptyAppException;
import model.exceptions.AppException;
import model.state.ExecutionStack;
import model.state.Output;
import model.state.ProgState;
import model.state.SymTable;
import model.statements.IStatement;
import repository.IRepository;
import repository.Repository;

public class Controller implements IController{
    IRepository repository;
    boolean displayFlag;

    public boolean getDisplayFlag() {
        return displayFlag;
    }

    @Override
    public void setDisplayFlag(boolean displayFlag) {
        this.displayFlag = displayFlag;
    }

    public Controller(boolean displayFlag) {
        repository = new Repository();
        this.displayFlag = displayFlag;
        if(this.displayFlag){
            this.displayCurrentState();
        }
    }

    public Controller(IStatement statement) {
        repository = new Repository();
        this.displayFlag = false;
    }

    @Override
    public void executeOneStep() throws AppException {
        ProgState state = repository.getCurrentProgram();
        IStatement statement = state.getExecutionStack().pop();
        statement.execute(state);
        if(this.displayFlag){
            this.displayCurrentState();
        }
    }

    @Override
    public void executeAllSteps() throws AppException {
        try{
            while(true){
                this.executeOneStep();
            }
        } catch(StackEmptyAppException exception){
            ;
        }
    }

    @Override
    public void displayCurrentState() {
        System.out.println(this.repository.getCurrentProgram().toDebug() + "\n");
    }

    @Override
    public void addProgram(IStatement statement) {
        this.repository.addProgram(new ProgState(new ExecutionStack(), new SymTable(), new Output(), statement));
    }
}
