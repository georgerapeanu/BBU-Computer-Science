package view.CLI.commands.get_commands;

import controller.parsers.syntax.SyntaxParser;
import model.exceptions.AppException;
import view.CLI.commands.IViewCommand;
import view.CLI.exceptions.ViewException;

public class GetHardcodedViewCommand implements IViewCommand {
    public GetHardcodedViewCommand() {
        ;
    }

    @Override
    public void execute(String command) throws AppException {
        System.out.println(SyntaxParser.parse(command.strip()).toJavaHardCode());
    }

    @Override
    public void addCommand(String command, IViewCommand viewCommand) throws AppException {
        throw new ViewException("Cannot add command to leaf run node!");
    }

    @Override
    public String getDescription(String prefix) {
        return prefix + ": Returns the hardcoded version of a toy language program";
    }
}
