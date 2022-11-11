package view.commands;

import model.exceptions.AppException;

public interface IViewCommand {
    public void execute(String command) throws AppException;
    public void addCommand(String command, IViewCommand viewCommand)throws AppException;
    public String getDescription(String prefix);
}
