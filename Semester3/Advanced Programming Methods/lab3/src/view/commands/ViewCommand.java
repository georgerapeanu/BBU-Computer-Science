package view.commands;

import model.exceptions.AppException;
import view.exceptions.ViewException;

import java.util.HashMap;
import java.util.Map;

public class ViewCommand implements IViewCommand{
    private Map<String, IViewCommand> commands;

    public ViewCommand(){
        this.commands = new HashMap<>();
    }

    @Override
    public void execute(String command) throws AppException {
        String[] args = command.trim().split(" ", 2);
        if(this.commands.containsKey(args[0])){
            String remaining = null;
            if(args.length > 1){
                remaining = args[1];
            }
            this.commands.get(args[0]).execute(remaining);
            return ;
        }
        throw new ViewException("No such command exists");
    }

    @Override
    public void addCommand(String command, IViewCommand viewCommand) {
        this.commands.put(command, viewCommand);
    }

    @Override
    public String getDescription(String prefix) {
        StringBuilder answer = new StringBuilder();
        for(String command:commands.keySet()){
            answer.append(commands.get(command).getDescription(prefix + " " + command));
        }
        return answer.toString();
    }
}
