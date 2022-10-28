package model.expressions;

import model.exceptions.AppException;
import model.state.ProgState;
import model.values.IValue;

public class BinaryExpression implements IExpression {
    IExpression left;
    IExpression right;
    String operator;

    public BinaryExpression(IExpression left, IExpression right, String operator) {
        this.left = left;
        this.right = right;
        this.operator = operator;
    }

    @Override
    public IValue evaluate(ProgState state) throws AppException {
        return left.evaluate(state).compose(right.evaluate(state), operator);
    }

    @Override
    public String toString(){
        return left.toString() + " " + operator + " " + right.toString();
    }
}
