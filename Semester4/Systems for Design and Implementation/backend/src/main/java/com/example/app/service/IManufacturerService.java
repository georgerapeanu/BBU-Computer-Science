package com.example.app.service;

import com.example.app.dto.ManufacturerProductCountDTO;
import com.example.app.dto.model.ManufacturerDTO;
import com.example.app.dto.model.ProductDTO;
import com.example.app.exceptions.AppException;
import org.springframework.data.domain.Page;

/**
 * The interface for manufacturer services.
 */
public interface IManufacturerService {

    /**
     * Retrieves all manufacturers with pagination.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing ManufacturerDTOs
     */
    Page<ManufacturerDTO> getAllManufacturers(Integer pageNumber, Integer pageSize);

    /**
     * Retrieves a manufacturer by its ID.
     *
     * @param id the ID of the manufacturer
     * @return the ManufacturerDTO object
     * @throws AppException if the manufacturer is not found
     */
    ManufacturerDTO getManufacturerById(Integer id) throws AppException;

    /**
     * Creates a new manufacturer.
     *
     * @param manufacturer the ManufacturerDTO object containing the details of the manufacturer
     * @throws AppException if there is an error during the creation of the manufacturer
     */
    void createManufacturer(ManufacturerDTO manufacturer) throws AppException;

    /**
     * Updates a manufacturer with the specified ID.
     *
     * @param id        the ID of the manufacturer to update
     * @param manufacturer the ManufacturerDTO object containing the updated details
     * @throws AppException if there is an error during the update of the manufacturer
     */
    void updateManufacturerWithId(Integer id, ManufacturerDTO manufacturer) throws AppException;

    /**
     * Deletes a manufacturer with the specified ID.
     *
     * @param id the ID of the manufacturer to delete
     */
    void deleteManufacturerWithId(Integer id);

    /**
     * Retrieves manufacturers sorted by the number of products they have.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing ManufacturerProductCountDTOs
     */
    Page<ManufacturerProductCountDTO> getManufacturersSortedByProducts(Integer pageNumber, Integer pageSize);

    /**
     * Retrieves a Page of ManufacturerProductCountDTOs with pagination.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing ManufacturerProductCountDTOs
     */
    Page<ManufacturerProductCountDTO> getManufacturerProductCountsPage(Integer pageNumber, Integer pageSize);
}
