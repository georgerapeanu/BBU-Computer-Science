package com.example.app.repository;

import com.example.app.dto.ManufacturerProductCountDTO;
import com.example.app.dto.model.ManufacturerDTO;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.List;

/**
 * Repository interface for managing manufacturers.
 */
public interface IManufacturerRepository {

    /**
     * Retrieves a page of manufacturers sorted by product count.
     *
     * @param pageable the pagination information
     * @return the page of manufacturers with their corresponding product counts
     */
    Page<ManufacturerProductCountDTO> getManufacturersSortedByProductCount(Pageable pageable);

    /**
     * Retrieves the product counts for a list of manufacturers.
     *
     * @param manufacturerDTOS the list of manufacturers
     * @return the list of manufacturers with their corresponding product counts
     */
    List<ManufacturerProductCountDTO> getManufacturerProductCountsFromList(List<ManufacturerDTO> manufacturerDTOS);

    /**
     * Retrieves the number of manufacturers associated with a user handle.
     *
     * @param userHandle the user handle
     * @return the number of manufacturers
     */
    Integer getManufacturerCountForUserHandle(String userHandle);
}
