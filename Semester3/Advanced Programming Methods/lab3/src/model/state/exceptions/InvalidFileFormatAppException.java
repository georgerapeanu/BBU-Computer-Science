package model.state.exceptions;

import model.exceptions.AppException;

public class InvalidFileFormatAppException extends AppException {
    public InvalidFileFormatAppException(String message) {
        super(message);
    }
}
