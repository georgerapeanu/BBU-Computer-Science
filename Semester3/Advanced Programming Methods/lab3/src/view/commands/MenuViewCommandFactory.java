package view.commands;

import controller.IController;
import model.exceptions.AppException;
import view.commands.get_commands.GetViewCommandFactory;
import view.commands.run_commands.RunProgramViewCommand;
import view.commands.run_commands.RunViewCommandFactory;
import view.commands.set_commands.SetViewCommandFactory;

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
