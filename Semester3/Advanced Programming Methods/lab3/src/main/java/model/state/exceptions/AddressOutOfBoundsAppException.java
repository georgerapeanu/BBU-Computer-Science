package model.state.exceptions;

import model.exceptions.AppException;

public class AddressOutOfBoundsAppException extends AppException {
    public AddressOutOfBoundsAppException(String message) {
        super(message);
    }
}
