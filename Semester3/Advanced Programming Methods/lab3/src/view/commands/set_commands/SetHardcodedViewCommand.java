package view.commands.set_commands;

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
import view.commands.IViewCommand;
import view.exceptions.ViewException;

import java.util.ArrayList;
import java.util.List;

public class SetHardcodedViewCommand implements IViewCommand {
    IController controller;
    List<IStatement> hardcoded_programs;

    public SetHardcodedViewCommand(IController controller) {
        this.controller = controller;
        this.hardcoded_programs = new ArrayList<>();
        this.hardcoded_programs.add(new CompositeStatement(new VariableDeclarationStatement("v",new IntegerType()), new CompositeStatement(new AssignmentStatement("v",new ConstantExpression(new IntegerValue(2))), new PrintStatement(new VariableExpression("v")))));
        this.hardcoded_programs.add(new CompositeStatement(new VariableDeclarationStatement("a",new IntegerType()), new CompositeStatement(new AssignmentStatement("a",new BinaryExpression(new ConstantExpression(new IntegerValue(2)),new BinaryExpression(new ConstantExpression(new IntegerValue(3)),new ConstantExpression(new IntegerValue(5)),"*"),"+")), new CompositeStatement(new VariableDeclarationStatement("b",new IntegerType()), new CompositeStatement(new AssignmentStatement("b",new BinaryExpression(new BinaryExpression(new VariableExpression("a"),new BinaryExpression(new ConstantExpression(new IntegerValue(4)),new ConstantExpression(new IntegerValue(2)),"/"),"-"),new ConstantExpression(new IntegerValue(7)),"+")), new PrintStatement(new VariableExpression("b")))))));
        this.hardcoded_programs.add(new CompositeStatement(new VariableDeclarationStatement("a",new BooleanType()), new CompositeStatement(new AssignmentStatement("a",new ConstantExpression(new BooleanValue(false))), new CompositeStatement(new VariableDeclarationStatement("v",new IntegerType()), new IfStatement(new VariableExpression("a"), new AssignmentStatement("v",new ConstantExpression(new IntegerValue(2))), new AssignmentStatement("v",new ConstantExpression(new IntegerValue(3))))))));
        this.hardcoded_programs.add(new CompositeStatement(new VariableDeclarationStatement("varf",new StringType()), new CompositeStatement(new AssignmentStatement("varf",new ConstantExpression(new StringValue("test.txt"))), new CompositeStatement(new OpenFileStatement(new VariableExpression("varf")), new CompositeStatement(new VariableDeclarationStatement("varc",new IntegerType()), new CompositeStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"), new CompositeStatement(new PrintStatement(new VariableExpression("varc")), new CompositeStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"), new CompositeStatement(new PrintStatement(new VariableExpression("varc")), new CloseFileStatement(new VariableExpression("varf")))))))))));
        this.hardcoded_programs.add(new CompositeStatement(new VariableDeclarationStatement("v",new RefType(new IntegerType())), new CompositeStatement(new NewStatement("v", new ConstantExpression(new IntegerValue(20))), new CompositeStatement(new VariableDeclarationStatement("a",new RefType(new RefType(new IntegerType()))), new CompositeStatement(new NewStatement("a", new VariableExpression("v")), new CompositeStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new VariableExpression("a"))))))));
        this.hardcoded_programs.add(new CompositeStatement(new VariableDeclarationStatement("v",new RefType(new IntegerType())), new CompositeStatement(new NewStatement("v", new ConstantExpression(new IntegerValue(20))), new CompositeStatement(new VariableDeclarationStatement("a",new RefType(new RefType(new IntegerType()))), new CompositeStatement(new NewStatement("a", new VariableExpression("v")), new CompositeStatement(new PrintStatement(new ReadHeapFunction(new VariableExpression("v"))), new PrintStatement(new BinaryExpression(new ReadHeapFunction(new ReadHeapFunction(new VariableExpression("a"))),new ConstantExpression(new IntegerValue(5)),"+"))))))));
        this.hardcoded_programs.add(new CompositeStatement(new VariableDeclarationStatement("v",new RefType(new IntegerType())), new CompositeStatement(new NewStatement("v", new ConstantExpression(new IntegerValue(20))), new CompositeStatement(new PrintStatement(new ReadHeapFunction(new VariableExpression("v"))), new CompositeStatement(new WriteHeapStatement(new VariableExpression("v"), new ConstantExpression(new IntegerValue(30))), new PrintStatement(new BinaryExpression(new ReadHeapFunction(new VariableExpression("v")),new ConstantExpression(new IntegerValue(5)),"+")))))));
        this.hardcoded_programs.add(new CompositeStatement(new VariableDeclarationStatement("v",new RefType(new IntegerType())), new CompositeStatement(new NewStatement("v", new ConstantExpression(new IntegerValue(20))), new CompositeStatement(new VariableDeclarationStatement("a",new RefType(new RefType(new IntegerType()))), new CompositeStatement(new NewStatement("a", new VariableExpression("v")), new CompositeStatement(new NewStatement("v", new ConstantExpression(new IntegerValue(30))), new PrintStatement(new ReadHeapFunction(new ReadHeapFunction(new VariableExpression("a"))))))))));
        this.hardcoded_programs.add(new CompositeStatement(new VariableDeclarationStatement("v",new IntegerType()), new CompositeStatement(new AssignmentStatement("v",new ConstantExpression(new IntegerValue(4))), new CompositeStatement(new WhileStatement(new BinaryExpression(new VariableExpression("v"),new ConstantExpression(new IntegerValue(0)),">"), new CompositeStatement(new PrintStatement(new VariableExpression("v")), new AssignmentStatement("v",new BinaryExpression(new VariableExpression("v"),new ConstantExpression(new IntegerValue(1)),"-")))), new PrintStatement(new VariableExpression("v"))))));
        this.hardcoded_programs.add(new CompositeStatement(new VariableDeclarationStatement("v",new IntegerType()), new CompositeStatement(new VariableDeclarationStatement("a",new RefType(new IntegerType())), new CompositeStatement(new AssignmentStatement("v",new ConstantExpression(new IntegerValue(10))), new CompositeStatement(new NewStatement("a", new ConstantExpression(new IntegerValue(22))), new CompositeStatement(new ForkStatement(new CompositeStatement(new WriteHeapStatement(new VariableExpression("a"), new ConstantExpression(new IntegerValue(30))), new CompositeStatement(new AssignmentStatement("v",new ConstantExpression(new IntegerValue(32))), new CompositeStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new ReadHeapFunction(new VariableExpression("a"))))))), new CompositeStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new ReadHeapFunction(new VariableExpression("a"))))))))));
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
