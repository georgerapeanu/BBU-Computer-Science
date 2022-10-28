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
    public void execute(ProgState progState) throws AppException {
        progState.getSymTable().setValue(variableName, expression.evaluate(progState));
    }

    @Override
    public String toString(){
        return variableName + "=" + expression.toString();
    }
}
