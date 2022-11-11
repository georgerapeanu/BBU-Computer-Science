package model.statements;

import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ProgState;
import model.values.IValue;
import model.values.StringValue;
import model.values.types.StringType;

public class CloseFileStatement implements IStatement{
    IExpression expression;

    public CloseFileStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public void execute(ProgState state) throws AppException {
        IValue value = this.expression.evaluate(state);
        if(!(value.getType() instanceof StringType)){
            throw new AppException("Filename did not evaluate to string");
        }
        state.getFileTable().closeFile(((StringValue)value).getValue());
    }

    @Override
    public String toString() {
        return "closeRFile(" + this.expression.toString() + ")";
    }
}
