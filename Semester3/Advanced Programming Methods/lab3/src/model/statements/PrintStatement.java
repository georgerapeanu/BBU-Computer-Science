package model.statements;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ProgState;
import model.values.types.IType;

public class PrintStatement implements IStatement {

    IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        state.getOutput().appendToOutput(expression.evaluate(state).toString());
        return null;
    }

    @Override
    public String toString(){
        return "print(" + expression.toString() + ")";
    }

    @Override
    public IGenericDictionary<String, IType> typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException {
        expression.typecheck(typeDictionary);
        return typeDictionary;
    }
}
