package model.state.exceptions;

import model.exceptions.AppException;

public class FileAlreadyOpenAppException extends AppException {
    public FileAlreadyOpenAppException(String message) {
        super(message);
    }
}
