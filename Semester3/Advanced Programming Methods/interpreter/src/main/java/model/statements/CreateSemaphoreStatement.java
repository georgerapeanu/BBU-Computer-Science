package model.statements;


import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ExecutionStack;
import model.state.ProgState;
import model.values.IValue;
import model.values.IntegerValue;
import model.values.types.BooleanType;
import model.values.types.IType;
import model.values.types.IntegerType;

public class CreateSemaphoreStatement implements IStatement{

    String name;
    IExpression expression;

    public CreateSemaphoreStatement(String name, IExpression expression) {
        this.name = name;
        this.expression = expression;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        IValue value = this.expression.evaluate(state);
        if(!(value.getType() instanceof IntegerType)) {
            throw new AppException("Invalid expression value for createSemaphore statement");
        }
        int count = ((IntegerValue)value).getValue();
        int semaphoreId = state.getSemaphoreTable().createSemaphore(count);
        state.getSymTable().setValue(name, new IntegerValue(semaphoreId));
        return null;
    }
    @Override
    public String toString(){
        return "createSemaphore(" + this.name + ", " + this.expression.toString() + ")";
    }

    @Override
    public IGenericDictionary<String, IType> typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException {
        IType type = this.expression.typecheck(typeDictionary);
        if(!type.equals(new IntegerType())){
            throw new AppException("Invalid expression type for create semaphore expression");
        }
        if(!typeDictionary.exists(this.name) || !typeDictionary.getValue(this.name).equals(new IntegerType())){
            throw new AppException("Invalid expression type for create semaphore variable");
        }
        return typeDictionary;
    }

    @Override
    public String toJavaHardCode() {
        return "new CreateSemaphoreStatement(\"" + this.name + "\", " + this.expression.toJavaHardCode() + ")";
    }
}
