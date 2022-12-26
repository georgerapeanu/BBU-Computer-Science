package model.expressions;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.state.ProgState;
import model.state.exceptions.SymbolNotFoundAppException;
import model.values.IValue;
import model.values.types.IType;

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
        return "(" + left.toString() + " " + operator + " " + right.toString() + ")";
    }

    @Override
    public IType typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException{
        IType firstType = left.typecheck(typeDictionary);
        IType secondType = right.typecheck(typeDictionary);
        if(firstType == null || !firstType.equals(secondType)) {
            throw new AppException("Binary expression operands are not the same");
        }
        return firstType;
    }
}
