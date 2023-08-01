package com.example.app.repository;

import com.example.app.dto.ProductScoreDTO;
import com.example.app.dto.model.ProductDTO;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.List;

/**
 * Repository interface for managing products.
 */
public interface IProductRepository {

    /**
     * Retrieves a page of products sorted by average score.
     *
     * @param pageable the pagination information
     * @return the page of products with their corresponding average scores
     */
    Page<ProductScoreDTO> getProductsSortedByAverageScore(Pageable pageable);

    /**
     * Retrieves the average scores for a list of products.
     *
     * @param productDTOS the list of products
     * @return the list of products with their corresponding average scores
     */
    List<ProductScoreDTO> getProductScoresFromList(List<ProductDTO> productDTOS);

    /**
     * Retrieves the number of products associated with a user handle.
     *
     * @param userHandle the user handle
     * @return the number of products
     */
    Integer getProductCountForUserHandle(String userHandle);
}
