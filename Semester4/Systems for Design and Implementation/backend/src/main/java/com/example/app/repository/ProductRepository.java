package com.example.app.repository;

import com.example.app.model.Manufacturer;
import com.example.app.model.Product;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * Repository interface for managing products.
 */
@Repository
public interface ProductRepository
        extends
        JpaRepository<Product, Integer>,
        JpaSpecificationExecutor<Product>,
        IProductRepository {
    Page<Product> findAllByManufacturer(Manufacturer manufacturer, PageRequest pageable);
}
