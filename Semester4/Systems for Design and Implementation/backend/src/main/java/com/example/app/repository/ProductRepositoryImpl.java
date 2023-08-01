package com.example.app.repository;

import com.example.app.dto.ProductScoreDTO;
import com.example.app.dto.model.ProductDTO;
import com.example.app.model.Manufacturer;
import com.example.app.model.Product;
import com.example.app.model.Review;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import jakarta.persistence.Tuple;
import jakarta.persistence.TypedQuery;
import jakarta.persistence.criteria.*;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageImpl;
import org.springframework.data.domain.Pageable;

import java.util.List;
import java.util.stream.Collectors;

public class ProductRepositoryImpl implements IProductRepository {

    @PersistenceContext
    private EntityManager em;

    /**
     * Retrieves a page of products sorted by the average score of their reviews.
     *
     * @param pageable the page request parameters
     * @return a page of ProductScoreDTO objects representing products and their average scores
     */
    @Override
    public Page<ProductScoreDTO> getProductsSortedByAverageScore(Pageable pageable) {
        CriteriaBuilder cb = em.getCriteriaBuilder();

        CriteriaQuery<Tuple> review_scores_cq = cb.createQuery(Tuple.class);
        Root<Review> review = review_scores_cq.from(Review.class);
        review_scores_cq
                .multiselect(review.get("product").get("id").alias("product_id"), cb.avg(cb.coalesce(review.get("score"), 0)).alias("score"))
                .groupBy(review.get("product").get("id"))
                .orderBy(cb.desc(cb.avg(cb.coalesce(review.get("score"), 0))));

        TypedQuery<Tuple> typedQuery = em.createQuery(review_scores_cq);

        List<ProductScoreDTO> results = typedQuery
                .setFirstResult(pageable.getPageNumber() * pageable.getPageSize())
                .setMaxResults(pageable.getPageSize())
                .getResultList()
                .stream()
                .map( row -> {
                        CriteriaQuery<Product> cq = cb.createQuery(Product.class);
                        Root<Product> product = cq.from(Product.class);
                        cq
                                .select(product)
                                .where(cb.equal(product.get("id"), row.get("product_id")));

                        return new ProductScoreDTO(
                                ProductDTO.fromProduct(em.createQuery(cq).getSingleResult()),
                                (Double)row.get("score")
                        );
                    }
                )
                .toList();

        CriteriaQuery<Long> count_cq = cb.createQuery(Long.class);
        Root<Review> review_count = count_cq.from(Review.class);
        count_cq.select(cb.countDistinct(review_count.get("product").get("id")));
        long total = em.createQuery(count_cq).getSingleResult();

        return new PageImpl<>(results, pageable, total);
    }

    /**
     * Retrieves the scores for a list of products.
     *
     * @param productDTOs the list of ProductDTO objects
     * @return a list of ProductScoreDTO objects representing the scores for the products
     */
    @Override
    public List<ProductScoreDTO> getProductScoresFromList(List<ProductDTO> productDTOs) {
        CriteriaBuilder cb = em.getCriteriaBuilder();

        CriteriaQuery<Tuple> review_scores_cq = cb.createQuery(Tuple.class);
        Root<Review> review = review_scores_cq.from(Review.class);
        CriteriaBuilder.In<Integer> inClause = cb.in(review.get("product").get("id"));
        for (ProductDTO productDTO : productDTOs) {
            inClause.value(productDTO.getId());
        }
        review_scores_cq
                .multiselect(review.get("product").get("id").alias("product_id"), cb.avg(cb.coalesce(review.get("score"), 0)).alias("score"))
                .groupBy(review.get("product").get("id"))
                .where(inClause);

        List<Tuple> typedQueryResult = em.createQuery(review_scores_cq).getResultList();

        return productDTOs.stream()
                .map(productDTO -> {
                    Double score = typedQueryResult.stream()
                            .filter(row -> row.get("product_id").equals(productDTO.getId()))
                            .map(row -> (Double)row.get("score"))
                            .findFirst()
                            .orElse(0.0);
                    return new ProductScoreDTO(productDTO, score);
                }).collect(Collectors.toList());
    }

    /**
     * Retrieves the number of products associated with the specified user handle.
     *
     * @param userHandle the user handle
     * @return the number of products
     */
    @Override
    public Integer getProductCountForUserHandle(String userHandle) {
        CriteriaBuilder cb = em.getCriteriaBuilder();
        CriteriaQuery<Long> cq = cb.createQuery(Long.class);
        Root<Product> product = cq.from(Product.class);
        Join<Manufacturer, Product> productManufacturerJoin = product.join("manufacturer", JoinType.LEFT);
        cq
                .select(cb.count(productManufacturerJoin))
                .where(cb.equal(productManufacturerJoin.get("user").get("handle"), userHandle));

        TypedQuery<Long> typedQuery = em.createQuery(cq);
        return typedQuery.getSingleResult().intValue();
    }
}
