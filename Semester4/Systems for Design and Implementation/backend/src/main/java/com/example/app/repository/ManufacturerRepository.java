package com.example.app.repository;

import com.example.app.model.Manufacturer;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

/**
 * Repository interface for managing manufacturers.
 */
@Repository
public interface ManufacturerRepository
        extends
            JpaRepository<Manufacturer, Integer>,
            JpaSpecificationExecutor<Manufacturer>,
            IManufacturerRepository {

}
