package view.commands.set_commands;

import controller.IController;
import model.exceptions.AppException;
import view.commands.IViewCommand;
import view.commands.ViewCommand;

public class SetViewCommandFactory {
    public static IViewCommand build(IController controller) throws AppException {
        IViewCommand viewCommand = new ViewCommand();
        viewCommand.addCommand("display", new SetDisplayFlagViewCommand(controller));
        viewCommand.addCommand("program", new SetProgramViewCommand(controller));
        viewCommand.addCommand("hardcoded", new SetHardcodedViewCommand(controller));
        return viewCommand;
    }
}
