package model.statements;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ProgState;
import model.values.IValue;
import model.values.StringValue;
import model.values.types.IType;
import model.values.types.StringType;

public class CloseFileStatement implements IStatement{
    IExpression expression;

    public CloseFileStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        IValue value = this.expression.evaluate(state);
        if(!(value.getType() instanceof StringType)){
            throw new AppException("Filename did not evaluate to string");
        }
        state.getFileTable().closeFile(((StringValue)value).getValue());
        return null;
    }

    @Override
    public String toString() {
        return "closeRFile(" + this.expression.toString() + ")";
    }

    @Override
    public IGenericDictionary<String, IType> typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException {
        if((new StringType()).equals(expression.typecheck(typeDictionary))){
            return typeDictionary;
        }
        throw new AppException("Close file expression doesn't evaluate to a StringType");
    }
}
