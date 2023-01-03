package model.values.exceptions;

import model.exceptions.AppException;

public class DivisionOverflowAppException extends AppException {
    public DivisionOverflowAppException(String message) {
        super(message);
    }
}
