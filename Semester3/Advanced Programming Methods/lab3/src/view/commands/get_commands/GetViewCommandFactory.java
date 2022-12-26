package view.commands.get_commands;

import model.exceptions.AppException;
import view.commands.IViewCommand;
import view.commands.ViewCommand;

public class GetViewCommandFactory {
    public static IViewCommand build() throws AppException {
        IViewCommand viewCommand = new ViewCommand();
        viewCommand.addCommand("hardcoded", new GetHardcodedViewCommand());
        return viewCommand;
    }
}
