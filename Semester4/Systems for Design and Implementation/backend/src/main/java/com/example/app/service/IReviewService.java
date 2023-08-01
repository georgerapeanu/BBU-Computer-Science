package com.example.app.service;

import com.example.app.dto.ProductScoreDTO;
import com.example.app.dto.model.ReviewDTO;
import com.example.app.exceptions.AppException;
import org.springframework.data.domain.Page;

/**
 * The interface for review services.
 */
public interface IReviewService {

    /**
     * Retrieves reviews for a user with pagination.
     *
     * @param handle     the user handle
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing ReviewDTOs
     * @throws AppException if there is an error retrieving the reviews
     */
    Page<ReviewDTO> getReviewsForUser(String handle, Integer pageNumber, Integer pageSize) throws AppException;

    /**
     * Retrieves reviews for a product with pagination.
     *
     * @param id         the ID of the product
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing ReviewDTOs
     * @throws AppException if there is an error retrieving the reviews
     */
    Page<ReviewDTO> getReviewsForProduct(Integer id, Integer pageNumber, Integer pageSize) throws AppException;

    /**
     * Retrieves a review for a user and a product.
     *
     * @param handle    the user handle
     * @param productId the ID of the product
     * @return the ReviewDTO object
     * @throws AppException if there is an error retrieving the review
     */
    ReviewDTO getReview(String handle, Integer productId) throws AppException;

    /**
     * Creates a new review.
     *
     * @param reviewDTO the ReviewDTO object containing the details of the review
     * @throws AppException if there is an error creating the review
     */
    void createReview(ReviewDTO reviewDTO) throws AppException;

    /**
     * Updates a review for a user and a product.
     *
     * @param handle    the user handle
     * @param productId the ID of the product
     * @param reviewDTO the ReviewDTO object containing the updated details
     * @throws AppException if there is an error updating the review
     */
    void updateReview(String handle, Integer productId, ReviewDTO reviewDTO) throws AppException;

    /**
     * Deletes a review for a user and a product.
     *
     * @param handle    the user handle
     * @param productId the ID of the product
     */
    void deleteReview(String handle, Integer productId);
}
