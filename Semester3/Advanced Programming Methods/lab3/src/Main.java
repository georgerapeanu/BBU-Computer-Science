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
import view.View;

public class Main {
    public static void main(String[] args) {
        View view = new View();
        view.run();
    }
}