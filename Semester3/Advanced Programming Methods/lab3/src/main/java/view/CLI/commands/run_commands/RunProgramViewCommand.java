package view.CLI.commands.run_commands;

import controller.IController;
import model.exceptions.AppException;
import view.CLI.commands.IViewCommand;
import view.CLI.exceptions.ViewException;

public class RunProgramViewCommand implements IViewCommand {
    IController controller;
    public RunProgramViewCommand(IController controller) {
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