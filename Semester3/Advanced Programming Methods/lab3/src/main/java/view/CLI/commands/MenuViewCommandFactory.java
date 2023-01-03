package view.CLI.commands;

import controller.IController;
import model.exceptions.AppException;
import view.CLI.commands.get_commands.GetViewCommandFactory;
import view.CLI.commands.run_commands.RunViewCommandFactory;
import view.CLI.commands.set_commands.SetViewCommandFactory;

public class MenuViewCommandFactory {
    public static IViewCommand build(IController controller) throws AppException {
        IViewCommand viewCommand = new ViewCommand();
        viewCommand.addCommand("get", GetViewCommandFactory.build());
        viewCommand.addCommand("set", SetViewCommandFactory.build(controller));
        viewCommand.addCommand("step", new StepViewCommand(controller));
        viewCommand.addCommand("run", RunViewCommandFactory.build(controller));
        viewCommand.addCommand("help", new HelpViewCommand(viewCommand));
        viewCommand.addCommand("exit", new ExitCommand());
        return viewCommand;
    }
}
