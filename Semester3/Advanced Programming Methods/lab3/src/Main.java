import controller.Controller;
import controller.IController;
import model.exceptions.AppException;
import model.expressions.BinaryExpression;
import model.expressions.ConstantExpression;
import model.expressions.VariableExpression;
import model.statements.*;
import model.values.IntegerValue;
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

        IController controller = new Controller(statement, true);
        controller.executeAllSteps();
    }
}