package com.example.app.repository;

import com.example.app.dto.UserReviewCountDTO;
import com.example.app.dto.model.UserProfileDTO;

import java.util.List;

/**
 * Repository interface for managing users.
 */
public interface IUserRepository {

    /**
     * Retrieves a list of user review counts from a list of user profiles.
     *
     * @param userProfiles the list of user profiles
     * @return the list of user review counts
     */
    List<UserReviewCountDTO> getUserReviewCountFromList(List<UserProfileDTO> userProfiles);
}
