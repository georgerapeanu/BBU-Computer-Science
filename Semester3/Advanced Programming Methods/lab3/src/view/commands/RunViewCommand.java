package view.commands;

import controller.IController;
import model.exceptions.AppException;
import view.exceptions.ViewException;

public class RunViewCommand implements IViewCommand{
    IController controller;
    public RunViewCommand(IController controller) {
        this.controller = controller;
    }

    @Override
    public void execute(String command) throws AppException {
        this.controller.executeAllSteps();
    }

    @Override
    public void addCommand(String command, IViewCommand viewCommand) throws AppException {
        throw new ViewException("Cannot add command to leaf run node!");
    }

    @Override
    public String getDescription(String prefix) {
        return prefix + ": Run all steps of the program\n";
    }
}
