package model.statements;

import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ProgState;
import model.values.BooleanValue;
import model.values.IValue;
import model.values.types.BooleanType;

public class IfStatement implements  IStatement{
    IExpression expression;
    IStatement left;
    IStatement right;

    public IfStatement(IExpression expression, IStatement left, IStatement right) {
        this.expression = expression;
        this.left = left;
        this.right = right;
    }

    @Override
    public void execute(ProgState state) throws AppException {
        IValue value = expression.evaluate(state);
        if(!(value.getType() instanceof BooleanType)) {
            throw new AppException("Invalid expression value for if statement");
        }
        if(((BooleanValue)value).getValue()){
            state.getExecutionStack().push(left);
        }else{
            state.getExecutionStack().push(right);
        }
    }

    @Override
    public String toString(){
        return "If(" + this.expression.toString() + ")" + "then {" + this.left.toString() + "} else {" + this.right.toString() + "}";
    }
}
