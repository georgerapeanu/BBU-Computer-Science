package view.CLI.commands.run_commands;

import controller.IController;
import model.exceptions.AppException;
import view.CLI.commands.IViewCommand;
import view.CLI.commands.ViewCommand;

public class RunViewCommandFactory {
    public static IViewCommand build(IController controller) throws AppException {
        IViewCommand viewCommand = new ViewCommand();
        viewCommand.addCommand("program", new RunProgramViewCommand(controller));
        return viewCommand;
    }
}
