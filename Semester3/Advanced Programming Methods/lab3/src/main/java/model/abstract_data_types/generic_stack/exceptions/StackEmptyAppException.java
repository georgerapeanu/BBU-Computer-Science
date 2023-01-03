package model.abstract_data_types.generic_stack.exceptions;

import model.exceptions.AppException;

public class StackEmptyAppException extends AppException {

    public StackEmptyAppException(String message) {
        super(message);
    }
}
