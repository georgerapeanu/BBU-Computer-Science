package model.statements;

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
    public void execute(ProgState progState) throws SymbolAlreadyExistsAppException {
        progState.getSymTable().declValue(name, type);
    }

    @Override
    public String toString(){
        return type.toString() + " " + name;
    }
}
