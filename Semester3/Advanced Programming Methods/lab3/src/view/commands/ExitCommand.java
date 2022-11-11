package view.commands;

import model.exceptions.AppException;
import view.exceptions.ViewException;

public class ExitCommand implements IViewCommand{
    public ExitCommand() {
        ;
    }

    @Override
    public void execute(String command) throws AppException {
        System.exit(0);
    }

    @Override
    public void addCommand(String command, IViewCommand viewCommand) throws AppException {
        throw new ViewException("Cannot add command to leaf exit node!");
    }

    @Override
    public String getDescription(String prefix) {
        return prefix + ": Exit the program\n";
    }
}
