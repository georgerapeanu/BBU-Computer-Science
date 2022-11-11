package view.commands;

import controller.IController;
import model.exceptions.AppException;
import view.commands.set_commands.SetViewCommandFactory;

public class MenuViewCommandFactory {
    public static IViewCommand build(IController controller) throws AppException {
        IViewCommand viewCommand = new ViewCommand();
        viewCommand.addCommand("set", SetViewCommandFactory.build(controller));
        viewCommand.addCommand("step", new StepViewCommand(controller));
        viewCommand.addCommand("run", new RunViewCommand(controller));
        viewCommand.addCommand("help", new HelpViewCommand(viewCommand));
        viewCommand.addCommand("exit", new ExitCommand());
        return viewCommand;
    }
}
