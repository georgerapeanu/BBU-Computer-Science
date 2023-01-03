package controller.parsers.expressions.exceptions;

import model.exceptions.AppException;

public class WrongMatchAppException extends AppException {
    public WrongMatchAppException(String message) {
        super(message);
    }
}
