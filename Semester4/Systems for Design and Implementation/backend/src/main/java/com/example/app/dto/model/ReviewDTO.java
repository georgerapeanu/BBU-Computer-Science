package com.example.app.dto.model;

import com.example.app.model.Product;
import com.example.app.model.Review;
import com.example.app.model.User;
import lombok.*;

import java.sql.Date;

/**
 * Data Transfer Object for Review.
 */
@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode
@ToString
public class ReviewDTO {
    @Getter
    @Setter
    private String userHandle;
    @Getter
    @Setter
    private Integer productId;
    @Getter
    @Setter
    private Integer score;
    @Getter
    @Setter
    private String comment;
    @Getter
    @Setter
    private Date postedDate;

    /**
     * Converts a Review object to a ReviewDTO object.
     *
     * @param review The Review object to convert.
     * @return The converted ReviewDTO object.
     */
    public static ReviewDTO fromReview(Review review) {
        return new ReviewDTO(
                review.getUser().getHandle(),
                review.getProduct().getId(),
                review.getScore(),
                review.getComment(),
                review.getPostedDate()
        );
    }

    /**
     * Converts a ReviewDTO object to a Review object.
     *
     * @param reviewDTO The ReviewDTO object to convert.
     * @param user      The User object associated with the review.
     * @param product   The Product object associated with the review.
     * @return The converted Review object.
     */
    public static Review toReview(ReviewDTO reviewDTO, User user, Product product) {
        Review review = new Review();
        review.setUser(user);
        review.setProduct(product);
        review.setScore(reviewDTO.getScore());
        review.setComment(reviewDTO.getComment());
        review.setPostedDate(reviewDTO.getPostedDate());
        return review;
    }
}
