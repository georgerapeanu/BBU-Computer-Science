package model.statements;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ProgState;
import model.state.exceptions.SymbolNotFoundAppException;
import model.values.types.IType;
import model.values.types.RefType;

public class AssignmentStatement implements  IStatement{
    String variableName;
    IExpression expression;

    public AssignmentStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        state.getSymTable().setValue(variableName, expression.evaluate(state));
        return null;
    }

    @Override
    public String toString(){
        return variableName + " = " + expression.toString();
    }

    @Override
    public IGenericDictionary<String, IType> typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException{
        IType variableType = typeDictionary.getValue(variableName);
        IType expressionType = expression.typecheck(typeDictionary);

        if(!expressionType.equals(variableType)){
            throw new AppException("Mismatched type in assignment");
        }
        return typeDictionary;
    }

    @Override
    public String toJavaHardCode() {
        return "new AssignmentStatement(" + "\"" + this.variableName + "\"" + "," + this.expression.toJavaHardCode() + ")";
    }
}
