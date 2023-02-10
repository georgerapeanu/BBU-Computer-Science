package model.state.exceptions;

import model.exceptions.AppException;

public class SymbolNotFoundAppException extends AppException {
    public SymbolNotFoundAppException(String message) {
        super(message);
    }
}
