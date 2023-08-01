package com.example.app.repository;

import com.example.app.model.Review;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import jakarta.persistence.TypedQuery;
import jakarta.persistence.criteria.CriteriaBuilder;
import jakarta.persistence.criteria.CriteriaQuery;
import jakarta.persistence.criteria.Root;

public class ReviewRepositoryImpl implements IReviewRepository {

    @PersistenceContext
    private EntityManager em;

    /**
     * Retrieves the number of reviews associated with the specified user handle.
     *
     * @param userHandle the user handle
     * @return the number of reviews
     */
    @Override
    public Integer getReviewCountForUserHandle(String userHandle) {
        CriteriaBuilder cb = em.getCriteriaBuilder();
        CriteriaQuery<Long> cq = cb.createQuery(Long.class);
        Root<Review> reviews = cq.from(Review.class);

        cq
                .select(cb.count(reviews))
                .where(cb.equal(reviews.get("user").get("handle"), userHandle));
        TypedQuery<Long> typedQuery = em.createQuery(cq);
        return typedQuery.getSingleResult().intValue();
    }
}
