package model.statements;

import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.exceptions.AppException;
import model.state.ProgState;
import model.state.exceptions.SymbolAlreadyExistsAppException;
import model.state.exceptions.SymbolNotFoundAppException;
import model.values.types.IType;

public class VariableDeclarationStatement implements IStatement{
    String name;
    IType type;

    public VariableDeclarationStatement(String name, IType type) {
        this.name = name;
        this.type = type;
    }
    @Override
    public ProgState execute(ProgState state) throws AppException {
        state.getSymTable().declValue(name, type);
        return null;
    }

    @Override
    public String toString(){
        return type.toString() + " " + name;
    }

    @Override
    public IGenericDictionary<String, IType> typecheck(IGenericDictionary<String, IType> typeDictionary) throws AppException {
        typeDictionary.setValue(name, type);
        return typeDictionary;
    }

    @Override
    public String toJavaHardCode() {
        return "new VariableDeclarationStatement(" + "\"" + name + "\"" + "," + this.type.toJavaHardCode() + ")";
    }
}
