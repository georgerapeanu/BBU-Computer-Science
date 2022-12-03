package controller;

import model.abstract_data_types.generic_stack.exceptions.StackEmptyAppException;
import model.exceptions.AppException;
import model.state.*;
import model.statements.IStatement;
import model.statements.NoOperationStatement;
import repository.IRepository;
import repository.Repository;

import java.io.IOException;

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

    public Controller(IRepository repository, boolean displayFlag) {
        this.repository = repository;
        this.displayFlag = displayFlag;
    }

    @Override
    public void executeOneStep() throws AppException{
        ProgState state = repository.getCurrentProgram();
        IStatement statement = state.getExecutionStack().pop();
        statement.execute(state);
        GarbageCollector.runGarbageCollector(repository.getCurrentProgram());
        if(this.displayFlag){
            this.displayCurrentState();
        }
        this.repository.logProgramState();
    }

    @Override
    public void executeAllSteps() throws AppException{
        try{
            while(true){
                this.executeOneStep();
            }
        } catch(StackEmptyAppException exception){
            ;
        } catch(AppException exception) {
            this.setProgram(new NoOperationStatement());
            throw exception;
        }
    }

    @Override
    public void displayCurrentState() throws AppException {
        System.out.println(this.repository.getCurrentProgram().toString() + "\n");
    }

    @Override
    public void setProgram(IStatement statement) throws AppException {
        this.repository.clear();
        this.repository.addProgram(new ProgState(new ExecutionStack(), new SymTable(), new Output(), new FileTable(), new Heap(), statement));
        this.repository.logProgramState();
        if(this.displayFlag){
            this.displayCurrentState();
        }
    }
}
