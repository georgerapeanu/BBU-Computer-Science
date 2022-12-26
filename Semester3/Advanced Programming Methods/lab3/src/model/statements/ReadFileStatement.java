package model.statements;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ProgState;
import model.values.IValue;
import model.values.IntegerValue;
import model.values.StringValue;
import model.values.types.IType;
import model.values.types.IntegerType;
import model.values.types.StringType;

public class ReadFileStatement implements  IStatement{
    IExpression expression;
    String name;

    public ReadFileStatement(IExpression expression, String name) {
        this.expression = expression;
        this.name = name;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        IValue value = this.expression.evaluate(state);
        if(!(value.getType() instanceof StringType)) {
            throw new AppException("Filename did not evaluate to string");
        }
        state.getSymTable().setValue(name, new IntegerValue(state.getFileTable().readFile(((StringValue)value).getValue())));
        return null;
    }

    @Override
    public String toString() {
        return "readFile(" + this.expression.toString() + ", " + this.name + ")";
    }

    @Override
    public IGenericDictionary<String, IType> typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException {
        if (!(new StringType()).equals(expression.typecheck(typeDictionary))) {
           throw new AppException("Read file expression does not evaluate to a string");
        }
        if (!typeDictionary.getValue(name).equals(new IntegerType())){
            throw new AppException("Read file value is not of IntegerType type");
        }
        return typeDictionary;
    }

    @Override
    public String toJavaHardCode() {
        return "new ReadFileStatement(" + expression.toJavaHardCode() + ", " + "\"" + this.name + "\"" + ")";
    }
}
