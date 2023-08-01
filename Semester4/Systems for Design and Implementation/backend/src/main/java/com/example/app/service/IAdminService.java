package com.example.app.service;

import com.example.app.exceptions.AppException;
import com.example.app.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

/**
 * The interface for administrative services.
 */
@Service
public interface IAdminService {

    /**
     * Drops all data from the relevant tables in the database.
     */
    void dropAll();

    /**
     * Repopulates the database with data.
     */
    void repopulateDb();

    /**
     * Changes the role of a user.
     *
     * @param user_handle the handle of the user
     * @param role        the new role for the user
     * @throws AppException if the user doesn't exist
     */
    void changeRole(String user_handle, String role) throws AppException;
}
