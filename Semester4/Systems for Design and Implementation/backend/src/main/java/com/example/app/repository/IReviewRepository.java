package com.example.app.repository;

/**
 * Repository interface for managing reviews.
 */
public interface IReviewRepository {

    /**
     * Retrieves the number of reviews associated with a user handle.
     *
     * @param userHandle the user handle
     * @return the number of reviews
     */
    Integer getReviewCountForUserHandle(String userHandle);
}
