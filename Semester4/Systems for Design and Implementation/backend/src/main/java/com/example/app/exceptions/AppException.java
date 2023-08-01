package com.example.app.exceptions;

/**
 * An exception specific to the application.
 */
public class AppException extends Exception {
    /**
     * Constructs a new AppException with the specified detail message.
     *
     * @param message the detail message
     */
    public AppException(String message) {
        super(message);
    }
}
