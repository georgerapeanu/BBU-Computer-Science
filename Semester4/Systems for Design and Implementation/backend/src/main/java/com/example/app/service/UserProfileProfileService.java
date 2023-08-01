package com.example.app.service;

import com.example.app.dto.UserCreatedCountDTO;
import com.example.app.dto.UserReviewCountDTO;
import com.example.app.model.UserProfile;
import com.example.app.dto.model.UserProfileDTO;
import com.example.app.repository.*;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageImpl;
import org.springframework.data.domain.PageRequest;
import org.springframework.stereotype.Service;
import org.springframework.beans.factory.annotation.Autowired;

/**
 * The user profile service implementation.
 */
@Service
public class UserProfileProfileService implements IUserProfileService {

    @Autowired
    UserRepository userRepository;

    @Autowired
    UserProfileRepository userProfileRepository;

    @Autowired
    ReviewRepository reviewRepository;

    @Autowired
    ProductRepository productRepository;

    @Autowired
    ManufacturerRepository manufacturerRepository;

    /**
     * Retrieves all user profiles with pagination.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing the list of UserProfileDTOs
     */
    @Override
    public Page<UserProfileDTO> getAllUserProfiles(Integer pageNumber, Integer pageSize) {
        return userProfileRepository
                .findAll(PageRequest.of(pageNumber, pageSize))
                .map(UserProfileDTO::fromUserProfile);
    }

    /**
     * Retrieves a user profile by handle.
     *
     * @param handle the user handle
     * @return the UserProfileDTO object
     */
    @Override
    public UserProfileDTO getUserProfileById(String handle) {
        UserProfile userProfile = userProfileRepository.findById(handle).orElse(null);
        if (userProfile == null) {
            return null;
        }
        return UserProfileDTO.fromUserProfile(userProfile);
    }

    /**
     * Creates a new user profile.
     *
     * @param userProfileDTO the UserProfileDTO object containing the user profile details
     */
    @Override
    public void createUserProfile(UserProfileDTO userProfileDTO) {
        userProfileRepository.save(UserProfileDTO.toUserProfile(userProfileDTO));
    }

    /**
     * Updates an existing user profile by handle.
     *
     * @param handle          the user handle
     * @param userProfileDTO the UserProfileDTO object containing the updated user profile details
     */
    @Override
    public void updateUserProfileWithId(String handle, UserProfileDTO userProfileDTO) {
        UserProfile userProfile = UserProfileDTO.toUserProfile(userProfileDTO);
        userProfile.setHandle(handle);
        userProfileRepository.save(userProfile);
    }

    /**
     * Deletes a user profile by handle.
     *
     * @param handle the user handle
     */
    @Override
    public void deleteUserProfileWithId(String handle) {
        userProfileRepository.deleteById(handle);
        userRepository.deleteById(handle);
    }

    /**
     * Retrieves a page of user review counts with pagination.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing the list of UserReviewCountDTOs
     */
    @Override
    public Page<UserReviewCountDTO> getUserReviewCountPage(Integer pageNumber, Integer pageSize) {
        Page<UserProfileDTO> userDTOPage = userProfileRepository
                .findAll(PageRequest.of(pageNumber, pageSize))
                .map(UserProfileDTO::fromUserProfile);

        return new PageImpl<>(
                userRepository.getUserReviewCountFromList(userDTOPage.getContent()),
                PageRequest.of(pageNumber, pageSize),
                userDTOPage.getTotalElements()
        );
    }

    /**
     * Retrieves the count of created items by a user.
     *
     * @param handle the user handle
     * @return the UserCreatedCountDTO object containing the count of created items
     */
    @Override
    public UserCreatedCountDTO getUserCreatedCount(String handle) {
        return new UserCreatedCountDTO(
                handle,
                reviewRepository.getReviewCountForUserHandle(handle),
                productRepository.getProductCountForUserHandle(handle),
                manufacturerRepository.getManufacturerCountForUserHandle(handle)
        );
    }
}
