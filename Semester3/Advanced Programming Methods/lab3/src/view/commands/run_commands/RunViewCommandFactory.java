package view.commands.run_commands;

import controller.IController;
import model.exceptions.AppException;
import view.commands.IViewCommand;
import view.commands.ViewCommand;
import view.commands.get_commands.GetHardcodedViewCommand;

public class RunViewCommandFactory {
    public static IViewCommand build(IController controller) throws AppException {
        IViewCommand viewCommand = new ViewCommand();
        viewCommand.addCommand("program", new RunProgramViewCommand(controller));
        return viewCommand;
    }
}
