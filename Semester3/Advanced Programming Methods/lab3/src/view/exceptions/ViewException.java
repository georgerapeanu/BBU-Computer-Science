package view.exceptions;

import model.exceptions.AppException;

public class ViewException extends AppException {
    public ViewException(String message) {
        super(message);
    }
}
