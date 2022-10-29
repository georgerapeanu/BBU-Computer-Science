package controller.parsers.expressions.exceptions;

import model.exceptions.AppException;

public class InvalidExpressionAppException extends AppException {

    public InvalidExpressionAppException(String message) {
        super(message);
    }
}
