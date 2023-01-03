package model.state.exceptions;

import model.exceptions.AppException;

public class FileNotOpenAppException extends AppException {
    public FileNotOpenAppException(String message) {
        super(message);
    }
}
