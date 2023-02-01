package model.statements;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.state.ProgState;
import model.values.IValue;
import model.values.IntegerValue;
import model.values.types.IType;
import model.values.types.IntegerType;

public class ReleaseStatement implements  IStatement{
    String name;

    public ReleaseStatement(String name) {
        this.name = name;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        IValue value = state.getSymTable().getValue(this.name);
        if(!(value.getType() instanceof IntegerType)) {
            throw new AppException("Invalid expression value for release statement");
        }
        int semaphoreId = ((IntegerValue)value).getValue();
        state.getSemaphoreTable().release(semaphoreId, state.getId());
        return null;
    }
    @Override
    public String toString(){
        return "release(\"" + this.name + "\")";
    }

    @Override
    public IGenericDictionary<String, IType> typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException {
        if(!typeDictionary.exists(this.name) || !typeDictionary.getValue(this.name).equals(new IntegerType())){
            throw new AppException("Invalid expression type for acquire variable");
        }
        return typeDictionary;
    }

    @Override
    public String toJavaHardCode() {
        return "new ReleaseStatement(\"" + this.name + "\")";
    }
}
