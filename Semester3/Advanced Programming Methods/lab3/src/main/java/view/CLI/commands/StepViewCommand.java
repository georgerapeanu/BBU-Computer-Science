package view.CLI.commands;

import controller.IController;
import model.exceptions.AppException;
import view.CLI.exceptions.ViewException;

public class StepViewCommand implements IViewCommand{
    IController controller;
    public StepViewCommand(IController controller) {
        this.controller = controller;
    }

    @Override
    public void execute(String command) throws AppException {
        this.controller.executeOneStep();
    }

    @Override
    public void addCommand(String command, IViewCommand viewCommand) throws AppException {
        throw new ViewException("Cannot add command to leaf step node!");
    }

    @Override
    public String getDescription(String prefix) {
        return prefix + ": Step once through the program\n";
    }
}
