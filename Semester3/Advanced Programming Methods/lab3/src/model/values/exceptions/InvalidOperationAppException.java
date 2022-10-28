package model.values.exceptions;

import model.exceptions.AppException;

public class InvalidOperationAppException extends AppException {
    public InvalidOperationAppException(String message) {
        super(message);
    }
}
