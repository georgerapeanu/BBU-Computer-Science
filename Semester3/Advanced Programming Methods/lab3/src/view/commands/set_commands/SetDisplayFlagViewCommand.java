package view.commands.set_commands;

import controller.IController;
import model.exceptions.AppException;
import view.commands.IViewCommand;
import view.exceptions.ViewException;

public class SetDisplayFlagViewCommand implements IViewCommand {
    IController controller;

    public SetDisplayFlagViewCommand(IController controller) {
        this.controller = controller;
    }

    @Override
    public void execute(String command) throws AppException {
        if(!command.trim().equals("false") && ! command.trim().equals("true")){
            throw new ViewException("Invalid boolean value " + command.trim());
        }
        this.controller.setDisplayFlag(Boolean.parseBoolean(command));
    }

    @Override
    public void addCommand(String command, IViewCommand viewCommand) throws ViewException {
        throw new ViewException("Cannot add command to leaf set display node!");
    }

    @Override
    public String getDescription(String prefix) {
        return prefix + ": Set the display flag to true/false\n";
    }
}
