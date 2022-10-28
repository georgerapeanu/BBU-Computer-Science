package controller;

import model.abstract_data_types.generic_stack.exceptions.StackEmptyAppException;
import model.exceptions.AppException;
import model.state.ProgState;
import model.statements.IStatement;
import repository.IRepository;
import repository.Repository;

public class Controller implements IController{
    IRepository repository;
    boolean displayFlag;

    public Controller(boolean displayFlag) {
        repository = new Repository();
        this.displayFlag = displayFlag;
        if(this.displayFlag){
            this.displayCurrentState();
        }
    }

    public Controller() {
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
        System.out.println(this.repository.getCurrentProgram().toDebug());
    }
}
