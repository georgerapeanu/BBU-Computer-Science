import controller.Controller;
import controller.IController;
import controller.parsers.expressions.ExpressionParser;
import controller.parsers.syntax.SyntaxParser;
import controller.parsers.syntax.SyntaxParser;
import model.exceptions.AppException;
import model.expressions.BinaryExpression;
import model.expressions.ConstantExpression;
import model.expressions.IExpression;
import model.expressions.VariableExpression;
import model.state.ExecutionStack;
import model.state.Output;
import model.state.ProgState;
import model.state.SymTable;
import model.statements.*;
import model.values.BooleanValue;
import model.values.IntegerValue;
import model.values.types.BooleanType;
import model.values.types.IntegerType;

public class Main {
    public static void main(String[] args) throws AppException {
        /*
        IStatement statement = new CompositeStatement(
                new VariableDeclarationStatement("v", new IntegerType()),
                new CompositeStatement(
                        new AssignmentStatement(
                                "v",
                                new ConstantExpression(new IntegerValue(2))
                        ),
                        new PrintStatement(
                                new VariableExpression("v")
                        )
                )
        );
         */

        /*
        IStatement statement = new CompositeStatement(
                new VariableDeclarationStatement("a",new IntegerType()),
                new CompositeStatement(
                        new VariableDeclarationStatement("b",new IntegerType()),
                        new CompositeStatement(
                                new AssignmentStatement("a",
                                        new BinaryExpression(
                                                new ConstantExpression(new IntegerValue(2)),
                                                new BinaryExpression(
                                                        new ConstantExpression(new IntegerValue(3)),
                                                        new ConstantExpression(new IntegerValue(5)),
                                                        "*"
                                                ),
                                                "+"
                                        )
                                ),
                                new CompositeStatement(
                                        new AssignmentStatement(
                                                "b",
                                                new BinaryExpression(
                                                        new VariableExpression("a"),
                                                        new ConstantExpression(new IntegerValue(1)),
                                                        "+"
                                                )
                                        ),
                                        new PrintStatement(new VariableExpression("b"))
                                )
                        )
                )
        );
         */
    /*
        IStatement statement = new CompositeStatement(
                new VariableDeclarationStatement("a",new BooleanType()),
                new CompositeStatement(
                        new VariableDeclarationStatement("v", new IntegerType()),
                        new CompositeStatement(
                                new AssignmentStatement("a", new BinaryExpression(
                                        new ConstantExpression(new BooleanValue(true)),
                                        new ConstantExpression(new BooleanValue(false)),
                                        "or"
                                )),
                                new CompositeStatement(
                                        new IfStatement(
                                                new VariableExpression("a"),
                                                new AssignmentStatement("v",new ConstantExpression(new IntegerValue(2))),
                                                new AssignmentStatement("v", new ConstantExpression(new IntegerValue(3)))
                                        ),
                                        new PrintStatement(new VariableExpression("v"))
                                )
                        )
                )
        );
        */
 //       IController controller = new Controller(statement, true);
 //       controller.executeAllSteps();
        //System.out.println(SyntaxParser.parse("IntegerType v;v=2;print(v);").toString());
        //System.out.println(SyntaxParser.parse("IntegerType a;a = 2 + 3 * 5;IntegerType b;b = a - 4/2 + 7;print(b);").toString());
        ///System.out.println(SyntaxParser.parse("{print(1);};").toString());
        ///TODO if with spaces instead of brackets
        System.out.println(SyntaxParser.parse("BooleanType a;a=false;IntegerType v;if a then v=2; else v=3;print(v);").toString());
    }
}