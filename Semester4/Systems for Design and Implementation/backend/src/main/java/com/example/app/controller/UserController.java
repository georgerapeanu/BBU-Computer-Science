package com.example.app.controller;

import com.example.app.dto.UserCreatedCountDTO;
import com.example.app.dto.UserReviewCountDTO;
import com.example.app.dto.model.ReviewDTO;
import com.example.app.dto.model.RoleDTO;
import com.example.app.dto.model.UserPreferenceDTO;
import com.example.app.dto.model.UserProfileDTO;
import com.example.app.exceptions.AppException;
import com.example.app.model.Role;
import com.example.app.model.User;
import com.example.app.model.UserPreference;
import com.example.app.service.IReviewService;
import com.example.app.service.IUserProfileService;
import com.example.app.service.IUserService;
import jakarta.validation.constraints.Max;
import jakarta.validation.constraints.Min;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import jakarta.validation.Valid;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

/**
 * Controller class that handles HTTP requests related to user management.
 */
@RestController
@CrossOrigin(origins = "*")
@Validated
public class UserController {

    @Autowired
    private IUserService userService;

    @Autowired
    private IUserProfileService userProfileService;

    @Autowired
    private IReviewService reviewService;

    /**
     * Retrieves a page of user profiles.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @param user       the authenticated user
     * @return a response entity containing the page of user profiles if successful,
     *         or an error response with the appropriate HTTP status
     */
    @GetMapping(path = "/users")
    public @ResponseBody ResponseEntity<Page<UserProfileDTO>> getUsers(
            @RequestParam
            Integer pageNumber,
            @RequestParam
            @Min(value=4, message = "pageSize should be at least 4")
            @Max(value=10, message = "pageSize should be at most 10")
            Integer pageSize,
            @RequestAttribute("user") User user
    ) {
        if (!user.getUserRole().getRead_all()) {
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        return new ResponseEntity<>(userProfileService.getAllUserProfiles(pageNumber, pageSize), HttpStatus.OK);
    }

    /**
     * Retrieves a user profile by handle.
     *
     * @param handle the handle of the user
     * @param user   the authenticated user
     * @return a response entity containing the user profile if found,
     *         or an error response with the appropriate HTTP status
     */
    @GetMapping(path = "/users/{id}", produces = "application/json")
    public @ResponseBody ResponseEntity<UserProfileDTO> getUser(
            @PathVariable("id") String handle,
            @RequestAttribute("user") User user
    ) {
        if (!user.getUserRole().getRead_all() && (!user.getUserRole().getRead_own() || !Objects.equals(user.getHandle(), handle))) {
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        UserProfileDTO userProfileDTO = userProfileService.getUserProfileById(handle);
        if (userProfileDTO == null) {
            return new ResponseEntity<>(null, HttpStatus.NOT_FOUND);
        } else {
            return new ResponseEntity<>(userProfileDTO, HttpStatus.OK);
        }
    }

    /**
     * Updates a user profile.
     *
     * @param handle         the handle of the user
     * @param userProfileDTO the updated user profile DTO
     * @param user           the authenticated user
     * @return a response entity indicating the status of the user profile update
     */
    @PatchMapping(path = "/users/{id}", produces = "application/json")
    public @ResponseBody ResponseEntity<Map<String, String>> updateUser(
            @PathVariable("id") String handle,
            @Valid @RequestBody UserProfileDTO userProfileDTO,
            @RequestAttribute("user") User user
    ) {
        Map<String, String> response = new HashMap<>();
        if (!user.getUserRole().getUpdate_all() && (!user.getUserRole().getUpdate_own() || !Objects.equals(user.getHandle(), handle))) {
            response.put("error", "Unauthorized to update resource");
            return new ResponseEntity<>(response, HttpStatus.UNAUTHORIZED);
        }
        userProfileService.updateUserProfileWithId(handle, userProfileDTO);
        response.put("message", "User profile updated");
        return new ResponseEntity<>(response, HttpStatus.OK);
    }

    /**
     * Deletes a user profile.
     *
     * @param handle the handle of the user
     * @param user   the authenticated user
     * @return a response entity indicating the status of the user profile deletion
     */
    @DeleteMapping(path = "/users/{id}", produces = "application/json")
    public @ResponseBody ResponseEntity<Map<String, String>> deleteUser(
            @PathVariable("id") String handle,
            @RequestAttribute("user") User user
    ) {
        Map<String, String> response = new HashMap<>();
        if (!user.getUserRole().getDelete_all() && (!user.getUserRole().getDelete_own() || !Objects.equals(user.getHandle(), handle))) {
            response.put("error", "Unauthorized to delete resource");
            return new ResponseEntity<>(response, HttpStatus.UNAUTHORIZED);
        }
        userProfileService.deleteUserProfileWithId(handle);
        response.put("message", "User profile deleted");
        return new ResponseEntity<>(response, HttpStatus.OK);
    }

    /**
     * Retrieves a page of reviews for a user.
     *
     * @param handle     the handle of the user
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @param user       the authenticated user
     * @return a response entity containing the page of reviews if successful,
     *         or an error response with the appropriate HTTP status
     */
    @GetMapping(path = "/users/{id}/reviews", produces = "application/json")
    public @ResponseBody ResponseEntity<Page<ReviewDTO>> getReviews(
            @PathVariable("id") String handle,
            @RequestParam
            Integer pageNumber,
            @RequestParam
            @Min(value=4, message = "pageSize should be at least 4")
            @Max(value=10, message = "pageSize should be at most 10")
            Integer pageSize,
            @RequestAttribute("user") User user
    ) {
        if (!user.getUserRole().getRead_all() && (!user.getUserRole().getRead_own() || !Objects.equals(user.getHandle(), handle))) {
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        try {
            return new ResponseEntity<>(reviewService.getReviewsForUser(handle, pageNumber, pageSize), HttpStatus.OK);
        } catch (AppException e) {
            return new ResponseEntity<>(null, HttpStatus.BAD_REQUEST);
        }
    }

    /**
     * Retrieves a page of user review counts.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @param user       the authenticated user
     * @return a response entity containing the page of user review counts if successful,
     *         or an error response with the appropriate HTTP status
     */
    @GetMapping(path = "/user-review-counts")
    public @ResponseBody ResponseEntity<Page<UserReviewCountDTO>> getUsersReviewCountPage(
            @RequestParam
            Integer pageNumber,
            @RequestParam
            @Min(value=4, message = "pageSize should be at least 4")
            @Max(value=10, message = "pageSize should be at most 10")
            Integer pageSize,
            @RequestAttribute("user") User user
    ) {
        if (!user.getUserRole().getRead_all()) {
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        return new ResponseEntity<>(userProfileService.getUserReviewCountPage(pageNumber, pageSize), HttpStatus.OK);
    }

    /**
     * Retrieves the user created count for a given user.
     *
     * @param handle the handle of the user
     * @param user   the authenticated user
     * @return a response entity containing the user created count if successful,
     *         or an error response with the appropriate HTTP status
     */
    @GetMapping(path = "/user-created-count/{handle}", produces = "application/json")
    public @ResponseBody ResponseEntity<UserCreatedCountDTO> getUserCreatedCount(
            @PathVariable("handle") String handle,
            @RequestAttribute("user") User user
    ) {
        if (!user.getUserRole().getRead_all() && (!user.getUserRole().getRead_own() || !Objects.equals(user.getHandle(), handle))) {
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        return new ResponseEntity<>(userProfileService.getUserCreatedCount(handle), HttpStatus.OK);
    }

    /**
     * Retrieves the role of a user.
     *
     * @param handle the handle of the user
     * @param user   the authenticated user
     * @return a response entity containing the user role if successful,
     *         or an error response with the appropriate HTTP status
     */
    @GetMapping(path = "/users/{handle}/role")
    public @ResponseBody ResponseEntity<RoleDTO> getUserRole(
            @PathVariable("handle") String handle,
            @RequestAttribute("user") User user
    ) {
        if (!user.getUserRole().getRead_all() && (!user.getUserRole().getRead_own() || !Objects.equals(handle, user.getHandle()))) {
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        try {
            return new ResponseEntity<>(RoleDTO.fromRole(userService.getUserByHandle(handle).getUserRole()), HttpStatus.OK);
        } catch (Exception e) {
            return new ResponseEntity<>(null, HttpStatus.BAD_REQUEST);
        }
    }

    /**
     * Retrieves the preference of a user.
     *
     * @param handle the handle of the user
     * @param user   the authenticated user
     * @return a response entity containing the user preference if successful,
     *         or an error response with the appropriate HTTP status
     */
    @GetMapping(path = "/users/{handle}/preference")
    public @ResponseBody ResponseEntity<UserPreferenceDTO> getUserPreference(
            @PathVariable("handle") String handle,
            @RequestAttribute("user") User user
    ) {
        if (!user.getUserRole().getRead_all() && (!user.getUserRole().getRead_own() || !Objects.equals(handle, user.getHandle()))) {
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        try {
            return new ResponseEntity<>(UserPreferenceDTO.fromUserPreference(userService.getUserByHandle(handle).getUserPreference()), HttpStatus.OK);
        } catch (Exception e) {
            return new ResponseEntity<>(null, HttpStatus.BAD_REQUEST);
        }
    }

    /**
     * Sets the preference of a user.
     *
     * @param handle            the handle of the user
     * @param user              the authenticated user
     * @param userPreferenceDTO the user preference DTO
     * @return a response entity indicating the status of the preference update
     */
    @PostMapping(path = "/users/{handle}/preference")
    public @ResponseBody ResponseEntity<Map<String, String>> setUserPreference(
            @PathVariable("handle") String handle,
            @RequestAttribute("user") User user,
            @RequestBody UserPreferenceDTO userPreferenceDTO
    ) {
        Map<String, String> response = new HashMap<>();
        if(!user.getUserRole().getUpdate_all() && (!user.getUserRole().getUpdate_own() || !Objects.equals(handle, user.getHandle()))) {
            response.put("error", "Unauthorized to update resource");
            return new ResponseEntity<>(response, HttpStatus.UNAUTHORIZED);
        }
        try {
            userService.setUserPreference(handle, UserPreferenceDTO.toUserPreference(userPreferenceDTO, userService.getUserByHandle(handle)));
            response.put("message", "updated preference");
            return new ResponseEntity<>(response, HttpStatus.OK);
        } catch (Exception e) {
            return new ResponseEntity<>(null, HttpStatus.BAD_REQUEST);
        }
    }
}
