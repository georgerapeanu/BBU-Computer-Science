package model.state.exceptions;

import model.exceptions.AppException;

public class SemaphoreAppException extends AppException {
    public SemaphoreAppException(String message) {
        super(message);
    }
}
