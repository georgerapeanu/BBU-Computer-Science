package model.statements;

import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ProgState;
import model.state.exceptions.SymbolNotFoundAppException;
import model.values.IValue;
import model.values.RefValue;

public class NewStatement implements IStatement{
    String name;
    IExpression expression;

    public NewStatement(String name, IExpression expression) {
        this.name = name;
        this.expression = expression;
    }

    @Override
    public void execute(ProgState state) throws AppException {
        IValue value = expression.evaluate(state);
        state.getSymTable().setValue(name, new RefValue(state.getHeap().allocate(value), value.getType()));
    }

    @Override
    public String toString(){
        return "new(" + this.name.toString() + ", " + this.expression.toString() + ")";
    }
}
