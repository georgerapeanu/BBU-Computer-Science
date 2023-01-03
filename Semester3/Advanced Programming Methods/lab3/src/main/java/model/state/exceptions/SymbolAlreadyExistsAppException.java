package model.state.exceptions;

import model.exceptions.AppException;

public class SymbolAlreadyExistsAppException extends AppException {
    public SymbolAlreadyExistsAppException(String message) {
        super(message);
    }
}
