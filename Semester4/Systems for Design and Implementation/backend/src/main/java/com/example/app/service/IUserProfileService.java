package com.example.app.service;

import com.example.app.dto.UserCreatedCountDTO;
import com.example.app.dto.UserReviewCountDTO;
import com.example.app.dto.model.UserProfileDTO;
import org.springframework.data.domain.Page;

/**
 * The interface for user profile services.
 */
public interface IUserProfileService {

    /**
     * Retrieves all user profiles with pagination.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing UserProfileDTOs
     */
    Page<UserProfileDTO> getAllUserProfiles(Integer pageNumber, Integer pageSize);

    /**
     * Retrieves a user profile by handle.
     *
     * @param handle the user handle
     * @return the UserProfileDTO object
     */
    UserProfileDTO getUserProfileById(String handle);

    /**
     * Creates a new user profile.
     *
     * @param userProfileDTO the UserProfileDTO object containing the details of the user profile
     */
    void createUserProfile(UserProfileDTO userProfileDTO);

    /**
     * Updates a user profile with the given handle.
     *
     * @param handle          the user handle
     * @param userProfileDTO the UserProfileDTO object containing the updated details
     */
    void updateUserProfileWithId(String handle, UserProfileDTO userProfileDTO);

    /**
     * Deletes a user profile with the given handle.
     *
     * @param handle the user handle
     */
    void deleteUserProfileWithId(String handle);

    /**
     * Retrieves a page of user review counts with pagination.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing UserReviewCountDTOs
     */
    Page<UserReviewCountDTO> getUserReviewCountPage(Integer pageNumber, Integer pageSize);

    /**
     * Retrieves the count of user profiles created by the user with the given handle.
     *
     * @param handle the user handle
     * @return the UserCreatedCountDTO object
     */
    UserCreatedCountDTO getUserCreatedCount(String handle);
}
