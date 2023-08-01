package com.example.app.repository;

import com.example.app.model.Ids.ReviewId;
import com.example.app.model.Product;
import com.example.app.model.Review;
import com.example.app.model.User;
import com.example.app.model.UserProfile;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

/**
 * Repository interface for managing reviews.
 */
@Repository
public interface ReviewRepository extends JpaRepository<Review, ReviewId>, JpaSpecificationExecutor<Review>, IReviewRepository {
    Page<Review> findAllByUser(User user, PageRequest pageable);
    Page<Review> findAllByProduct(Product product, PageRequest pageable);
}
