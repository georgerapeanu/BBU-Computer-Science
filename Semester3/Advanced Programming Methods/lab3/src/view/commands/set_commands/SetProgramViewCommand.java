package view.commands.set_commands;

import controller.IController;
import controller.parsers.syntax.SyntaxParser;
import model.exceptions.AppException;
import view.commands.IViewCommand;
import view.exceptions.ViewException;

public class SetProgramViewCommand implements IViewCommand {
    IController controller;

    public SetProgramViewCommand(IController controller) {
        this.controller = controller;
    }

    @Override
    public void execute(String command) throws AppException {
        this.controller.setProgram(SyntaxParser.parse(command.strip()));
    }

    @Override
    public void addCommand(String command, IViewCommand viewCommand) throws AppException {
        throw new ViewException("Cannot add command to leaf set program node!");
    }

    @Override
    public String getDescription(String prefix) {
        return prefix + ": Set the program to supplied PROGRAM\n";
    }
}
