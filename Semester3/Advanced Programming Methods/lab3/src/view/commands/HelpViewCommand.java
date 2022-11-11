package view.commands;

import model.exceptions.AppException;
import view.exceptions.ViewException;

public class HelpViewCommand implements IViewCommand{

    IViewCommand root;

    public HelpViewCommand(IViewCommand root) {
        this.root = root;
    }

    @Override
    public void execute(String command) throws AppException {
        System.out.println("Usage: ");
        System.out.print(this.root.getDescription(""));
    }

    @Override
    public void addCommand(String command, IViewCommand viewCommand) throws AppException {
        throw new ViewException("Cannot add command to leaf help node!");
    }

    @Override
    public String getDescription(String prefix) {
        return prefix + ": Describes program functionalities\n";
    }
}
