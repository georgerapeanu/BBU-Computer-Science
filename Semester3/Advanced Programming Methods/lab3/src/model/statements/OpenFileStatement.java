package model.statements;

import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ProgState;
import model.values.IValue;
import model.values.StringValue;
import model.values.types.StringType;

public class OpenFileStatement implements IStatement{
    IExpression expression;

    public OpenFileStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        IValue value = this.expression.evaluate(state);
        if(!(value.getType() instanceof StringType)){
            throw new AppException("Filename did not evaluate to string");
        }
        state.getFileTable().openFile(((StringValue)value).getValue());
        return null;
    }

    @Override
    public String toString() {
        return "openRFile(" + this.expression.toString() + ")";
    }
}
