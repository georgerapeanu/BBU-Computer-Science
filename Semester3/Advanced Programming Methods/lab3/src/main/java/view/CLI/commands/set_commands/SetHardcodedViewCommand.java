package view.CLI.commands.set_commands;

import controller.IController;
import model.exceptions.AppException;
import model.expressions.BinaryExpression;
import model.expressions.ConstantExpression;
import model.expressions.ReadHeapFunction;
import model.expressions.VariableExpression;
import model.statements.*;
import model.values.BooleanValue;
import model.values.IntegerValue;
import model.values.StringValue;
import model.values.types.BooleanType;
import model.values.types.IntegerType;
import model.values.types.RefType;
import model.values.types.StringType;
import utils.HardcodedPrograms;
import view.CLI.commands.IViewCommand;
import view.CLI.exceptions.ViewException;

import java.util.ArrayList;
import java.util.List;

public class SetHardcodedViewCommand implements IViewCommand {
    IController controller;
    List<IStatement> hardcoded_programs;

    public SetHardcodedViewCommand(IController controller) {
        this.controller = controller;
        this.hardcoded_programs = HardcodedPrograms.hardcodedPrograms;
    }

    @Override
    public void execute(String command) throws AppException {
        int value;
        try{
            value = Integer.parseInt(command.trim());
        } catch (NumberFormatException exception){
            throw new ViewException("Program id not recognized");
        }
        if(value < 0 || value >= hardcoded_programs.size()){
            throw new ViewException("Program id not recognized");
        }
        this.controller.setProgram(hardcoded_programs.get(value));
    }

    @Override
    public void addCommand(String command, IViewCommand viewCommand) throws AppException {
        throw new ViewException("Cannot add command to leaf run node!");
    }

    @Override
    public String getDescription(String prefix) {
        StringBuilder answer = new StringBuilder(prefix + ": Runs one of the following programs:");
        int i = 0;
        while(i < hardcoded_programs.size()) {
            answer.append("\n\t").append(Integer.toString(i));
            answer.append(": ").append(hardcoded_programs.get(i).toString());
            i++;
        }
        answer.append("\n");
        return answer.toString();
    }
}
