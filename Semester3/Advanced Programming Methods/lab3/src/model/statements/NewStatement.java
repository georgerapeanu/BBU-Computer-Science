package model.statements;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ProgState;
import model.state.exceptions.SymbolNotFoundAppException;
import model.values.IValue;
import model.values.RefValue;
import model.values.types.IType;
import model.values.types.IntegerType;
import model.values.types.RefType;

public class NewStatement implements IStatement{
    String name;
    IExpression expression;

    public NewStatement(String name, IExpression expression) {
        this.name = name;
        this.expression = expression;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        IValue value = expression.evaluate(state);
        state.getSymTable().setValue(name, new RefValue(state.getHeap().allocate(value), value.getType()));
        return null;
    }

    @Override
    public String toString(){
        return "new(" + this.name.toString() + ", " + this.expression.toString() + ")";
    }

    @Override
    public IGenericDictionary<String, IType> typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException {
        IType variableType = typeDictionary.getValue(name);
        IType expressionType = expression.typecheck(typeDictionary);
        if(variableType != null && variableType.equals(new RefType(expressionType))){
            return typeDictionary;
        }
        throw new AppException("Mismatched types for new statement");
    }

    @Override
    public String toJavaHardCode() {
        return "new NewStatement(" + "\"" + this.name + "\"" + ", " + this.expression.toJavaHardCode() + ")";
    }
}
