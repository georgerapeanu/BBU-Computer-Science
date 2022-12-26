package model.statements;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.expressions.IExpression;
import model.state.ProgState;
import model.values.IValue;
import model.values.RefValue;
import model.values.types.IType;
import model.values.types.RefType;

public class WriteHeapStatement implements IStatement{
    IExpression addressExpression;
    IExpression valueExpression;

    public WriteHeapStatement(IExpression addressExpression, IExpression valueExpression) {
        this.addressExpression = addressExpression;
        this.valueExpression = valueExpression;
    }

    @Override
    public ProgState execute(ProgState state) throws AppException {
        IValue address = addressExpression.evaluate(state);
        IValue value = valueExpression.evaluate(state);
        if(!(address.getType() instanceof RefType)){
            throw new AppException("Heap should be accessed only using references");
        }
        state.getHeap().write(((RefValue)address).getAddress(), value);
        return null;
    }
    @Override
    public String toString(){
        return "writeHeap(" + addressExpression.toString() + ", " + valueExpression.toString() + ")";
    }

    @Override
    public IGenericDictionary<String, IType> typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException {
        IType addressType = addressExpression.typecheck(typeDictionary);
        valueExpression.typecheck(typeDictionary);
        if(!(addressType instanceof RefType)) {
            throw new AppException("Write heap expression does not evaluate to a RefType");
        }
        return typeDictionary;
    }
}
