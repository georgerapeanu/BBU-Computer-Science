package view;

import controller.IController;
import controller.parsers.syntax.SyntaxParser;
import model.exceptions.AppException;
import model.statements.NoOperationStatement;
import view.commands.IViewCommand;
import view.commands.MenuViewCommandFactory;
import view.exceptions.ViewException;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Objects;

public class MainView implements IMainView {
    IController controller;
    IViewCommand commandMenu;

    public MainView(IController controller) throws AppException {
        this.controller = controller;
        this.commandMenu = MenuViewCommandFactory.build(controller);
    }

    @Override
    public void run() throws AppException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        while(true){
            try{
                System.out.print("Enter command>");
                String cmd = reader.readLine().strip();
                this.commandMenu.execute(cmd);
            } catch (AppException exception){
                System.out.println(exception.getMessage());
                this.controller.setProgram(new NoOperationStatement());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
