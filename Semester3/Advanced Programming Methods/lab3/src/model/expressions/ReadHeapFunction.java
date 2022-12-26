package model.expressions;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.state.ProgState;
import model.values.IValue;
import model.values.RefValue;
import model.values.types.IType;
import model.values.types.RefType;

import java.sql.Ref;

public class ReadHeapFunction implements IExpression{

    IExpression expr;

    public ReadHeapFunction(IExpression expr) {
        this.expr = expr;
    }

    @Override
    public IValue evaluate(ProgState state) throws AppException {
        IValue value = expr.evaluate(state);
        if(!(value.getType() instanceof RefType)){
            throw new AppException("Heap should only be accessed through references");
        }
        return state.getHeap().read(((RefValue)value).getAddress());
    }

    @Override
    public String toString(){
        return "readHeap(" + expr.toString() + ")";
    }

    @Override
    public IType typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException {
        if(!(expr.typecheck(typeDictionary) instanceof RefType)) {
            throw new AppException("Read Heap expression evaluates to a non RefType");
        }
        return null;
    }
}
