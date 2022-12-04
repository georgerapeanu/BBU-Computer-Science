package model.statements;

import model.exceptions.AppException;
import model.state.ProgState;
import model.state.exceptions.SymbolAlreadyExistsAppException;
import model.state.exceptions.SymbolNotFoundAppException;

public interface IStatement {
    public ProgState execute(ProgState state) throws AppException;
    public String toString();
}
