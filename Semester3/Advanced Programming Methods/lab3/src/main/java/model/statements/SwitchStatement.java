package model.statements;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.abstract_data_types.generic_list.IGenericList;
import model.exceptions.AppException;
import model.expressions.BinaryExpression;
import model.expressions.IExpression;
import model.state.ProgState;
import model.values.types.IType;

import java.util.Arrays;
import java.util.List;

/// statements should have 1 more element, the last one is the default
public class SwitchStatement implements IStatement {
    IExpression expression;
    IGenericList<IExpression> expressions;
    IGenericList<IStatement> statements;

    public SwitchStatement(IExpression expression, IGenericList<IExpression> expressions, IGenericList<IStatement> statements) {
        this.expression = expression;
        this.expressions = expressions;
        this.statements = statements;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        List<IExpression> expressions = this.expressions.getAll();
        List<IStatement> statements = this.statements.getAll();
        IStatement statement = statements.get(statements.size() - 1);
        for(int i = expressions.size() - 1;i >= 0;i--){
            statement = new IfStatement(new BinaryExpression(expression, expressions.get(i), "=="), statements.get(i), statement);
        }
        state.getExecutionStack().push(statement);
        return null;
    }

    @Override
    public IGenericDictionary<String, IType> typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException {
        IType expressionType = expression.typecheck(typeDictionary);
        for(IStatement iter_statement:this.statements.getAll()){
            iter_statement.typecheck(typeDictionary.copy());
        }

        for(IExpression iter_expression:this.expressions.getAll()){
            if(!(iter_expression.typecheck(typeDictionary).equals(expressionType))) {
                throw new AppException("Expression type mismatch in switch");
            }
        }
        return typeDictionary;
    }

    @Override
    public String toJavaHardCode() {
        List<IExpression> expressions = this.expressions.getAll();
        List<IStatement> statements = this.statements.getAll();
        StringBuilder answer = new StringBuilder("new SwitchStatement(" + this.expression.toJavaHardCode() + ",");
        answer.append("new GenericList<>(Arrays.asList(");
        for(int i = 0;i < expressions.size();i++){
            answer.append(expressions.get(i).toJavaHardCode());
            if(i + 1 < expressions.size()){
                answer.append(",");
            }
        }
        answer.append(")),");

        answer.append("new GenericList<>(Arrays.asList(");
        for(int i = 0;i < statements.size();i++){
            answer.append(statements.get(i).toJavaHardCode());
            if(i + 1 < statements.size()){
                answer.append(",");
            }
        }
        answer.append(")))");
        return answer.toString();
    }

    @Override
    public String toString(){
        StringBuilder answer = new StringBuilder("switch(" + this.expression.toString() + ")");
        List<IExpression> expressions = this.expressions.getAll();
        List<IStatement> statements = this.statements.getAll();
        for(int i = 0;i < expressions.size();i++){
            answer.append("(case ").append(expressions.get(i).toString()).append(": ").append(statements.get(i).toString()).append(")");
        }
        answer.append("(default: ").append(statements.get(statements.size() - 1)).append(");");
        return answer.toString();
    }
}

