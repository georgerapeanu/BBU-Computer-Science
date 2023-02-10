package model.abstract_data_types.generic_dictionary.exceptions;

import model.exceptions.AppException;

public class KeyNotFoundAppException extends AppException {
    public KeyNotFoundAppException(String message) {
        super(message);
    }
}
