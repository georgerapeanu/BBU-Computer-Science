package view.CLI.commands.set_commands;

import controller.IController;
import controller.parsers.syntax.SyntaxParser;
import model.exceptions.AppException;
import view.CLI.commands.IViewCommand;
import view.CLI.exceptions.ViewException;

public class SetProgramViewCommand implements IViewCommand {
    IController controller;

    public SetProgramViewCommand(IController controller) {
        this.controller = controller;
    }

    @Override
    public void execute(String command) throws AppException {
        if(command == null){
            throw new ViewException("Invalid command");
        }
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
