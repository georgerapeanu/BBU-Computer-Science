package com.example.app.service;

import com.example.app.exceptions.AppException;
import com.example.app.model.User;
import com.example.app.model.UserPreference;

/**
 * The interface for user services.
 */
public interface IUserService {

    /**
     * Retrieves a user by handle.
     *
     * @param handle the user handle
     * @return the User object
     * @throws AppException if the user is not found
     */
    User getUserByHandle(String handle) throws AppException;

    /**
     * Sets the user preference for the user with the given handle.
     *
     * @param handle          the user handle
     * @param userPreference the UserPreference object containing the user's preference
     * @throws AppException if the user is not found
     */
    void setUserPreference(String handle, UserPreference userPreference) throws AppException;
}
