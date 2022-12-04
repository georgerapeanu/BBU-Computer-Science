package model.statements;

import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ProgState;
import model.state.exceptions.SymbolNotFoundAppException;

public class AssignmentStatement implements  IStatement{
    String variableName;
    IExpression expression;

    public AssignmentStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        state.getSymTable().setValue(variableName, expression.evaluate(state));
        return null;
    }

    @Override
    public String toString(){
        return variableName + " = " + expression.toString();
    }
}
