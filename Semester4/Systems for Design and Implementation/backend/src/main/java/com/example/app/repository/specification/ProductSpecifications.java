package com.example.app.repository.specification;

import com.example.app.model.Product;
import org.springframework.data.jpa.domain.Specification;

/**
 * Specifications for querying products.
 */
public class ProductSpecifications {

    /**
     * Creates a specification for querying products with weight greater than the given weight.
     *
     * @param weight The weight to compare against.
     * @return The specification for weight comparison.
     */
    public static Specification<Product> weightBiggerThan(Integer weight) {
        return (product, cq, cb) -> cb.greaterThan(product.get("weight"), weight);
    }
}
