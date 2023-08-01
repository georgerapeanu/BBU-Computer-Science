package com.example.app.service;

import com.example.app.exceptions.AppException;
import com.example.app.model.User;
import org.springframework.web.bind.annotation.RequestBody;

/**
 * The interface for user login services.
 */
public interface ILoginService {

    /**
     * Registers a new user.
     *
     * @param user the user object containing registration details
     * @return a token representing the registered user
     * @throws AppException if there is an error during registration
     */
    String register(@RequestBody User user) throws AppException;

    /**
     * Logs in a user.
     *
     * @param user the user object containing login credentials
     * @return a token representing the logged-in user
     * @throws AppException if there is an error during login
     */
    String login(@RequestBody User user) throws AppException;

    /**
     * Activates a user account.
     *
     * @param token the activation token associated with the user account
     * @throws AppException if there is an error during activation
     */
    void activateUser(@RequestBody String token) throws AppException;
}
