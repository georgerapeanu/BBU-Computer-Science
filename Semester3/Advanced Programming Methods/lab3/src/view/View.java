package view;

import controller.Controller;
import controller.IController;
import controller.parsers.expressions.exceptions.InvalidExpressionAppException;
import controller.parsers.syntax.SyntaxParser;
import controller.parsers.syntax.exceptions.SyntaxAppException;
import model.exceptions.AppException;
import model.statements.NoOperationStatement;
import view.exceptions.ViewException;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Objects;

public class View implements  IView {
    IController controller;

    public View(IController controller) {
        this.controller = controller;
    }

    @Override
    public void run() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        while(true){
            try{
                System.out.print("Enter command>");
                String cmd = reader.readLine().strip();
                String[] args = cmd.split(" ");
                if(args.length > 0){
                    if(args.length > 1 && Objects.equals(args[0].toLowerCase(), "set") && Objects.equals(args[1].toLowerCase(), "display")){
                        this.handleSetDisplayFlag(args);
                    }else if(args.length > 1 && Objects.equals(args[0].toLowerCase(), "set") && Objects.equals(args[1].toLowerCase(), "program")){
                        this.handleSetProgram(args);
                    } else if(Objects.equals(args[0].toLowerCase(), "step")){
                        this.handleSingleStep();
                    } else if(Objects.equals(args[0].toLowerCase(), "run")){
                        this.handleRun();
                    }else if(Objects.equals(args[0].toLowerCase(), "help")){
                        this.handleHelp();
                    }else if(Objects.equals(args[0].toLowerCase(), "exit")){
                        break;
                    }else{
                        throw new ViewException("Invalid command!");
                    }
                } else {
                    throw new ViewException("Invalid command!");
                }
            } catch (IOException exception) {
                break;
            } catch (AppException exception){
                System.out.println(exception.getMessage());
                this.controller.setProgram(new NoOperationStatement());
            }
        }

    }

    private void handleSetProgram(String[] args) throws AppException, IOException {
        StringBuilder program = new StringBuilder();
        for(int i = 2;i < args.length;i++){
            program.append(args[i]);
            if(i + 1 < args.length){
                program.append(" ");
            }
        }
        this.controller.setProgram(SyntaxParser.parse(program.toString()));
    }

    private void handleSetDisplayFlag(String[] args) throws ViewException {
        if(args.length != 3){
            throw new ViewException("Invalid arguments for setting the display flag!");
        }
        if(!args[2].trim().equals("false") && ! args[2].trim().equals("true")){
            throw new ViewException("Invalid boolean value " + args[2].trim());
        }
        this.controller.setDisplayFlag(Boolean.parseBoolean(args[2]));
    }

    private void handleSingleStep() throws AppException, IOException {
        this.controller.executeOneStep();
    }

    private void handleRun() throws AppException, IOException {
        this.controller.executeAllSteps();
    }

    private void handleHelp() {
        System.out.println("Usage:");
        System.out.println("set display true/false");
        System.out.println("set program PROGRAM");
        System.out.println("step");
        System.out.println("run");
        System.out.println("help");
        System.out.println("exit");
    }
}
