package com.example.app.repository;

import com.example.app.dto.UserReviewCountDTO;
import com.example.app.dto.model.UserDTO;
import com.example.app.dto.model.UserProfileDTO;
import com.example.app.model.Review;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import jakarta.persistence.Tuple;
import jakarta.persistence.criteria.CriteriaBuilder;
import jakarta.persistence.criteria.CriteriaQuery;
import jakarta.persistence.criteria.Root;

import java.util.List;
import java.util.stream.Collectors;

public class UserRepositoryImpl implements IUserRepository {

    @PersistenceContext
    EntityManager em;

    /**
     * Retrieves the review counts for the given list of user profiles.
     *
     * @param userProfiles the list of user profiles
     * @return the list of user review counts
     */
    public List<UserReviewCountDTO> getUserReviewCountFromList(List<UserProfileDTO> userProfiles) {
        CriteriaBuilder cb = em.getCriteriaBuilder();
        CriteriaQuery<Tuple> user_review_count_cq = cb.createQuery(Tuple.class);
        Root<Review> review = user_review_count_cq.from(Review.class);
        CriteriaBuilder.In<String> inClause = cb.in(review.get("user").get("handle"));
        for(UserProfileDTO userProfileDTO : userProfiles) {
            inClause.value(userProfileDTO.getHandle());
        }
        user_review_count_cq
                .multiselect(review.get("user").get("handle").alias("handle"), cb.count(review.get("product").get("id")).alias("count"))
                .groupBy(review.get("user").get("handle"))
                .where(inClause);

        List<Tuple> typedQueryResult = em.createQuery(user_review_count_cq).getResultList();

        return userProfiles.stream()
                .map(user -> {
                    Integer count = typedQueryResult.stream()
                            .filter(row -> row.get("handle").equals(user.getHandle()))
                            .findFirst()
                            .map(row -> (Long)row.get("count"))
                            .map(Long::intValue)
                            .orElse(0);
                    return new UserReviewCountDTO(user, count);
                }).collect(Collectors.toList());
    }
}
