package com.example.app.service;

import com.example.app.dto.ManufacturerProductCountDTO;
import com.example.app.dto.ProductScoreDTO;
import com.example.app.dto.ProductScoreWithUserHandleDTO;
import com.example.app.dto.model.ManufacturerDTO;
import com.example.app.dto.model.ProductDTO;
import com.example.app.exceptions.AppException;
import com.example.app.model.User;
import org.springframework.data.domain.Page;

/**
 * The interface for product services.
 */
public interface IProductService {

    /**
     * Retrieves all products with pagination.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing ProductDTOs
     */
    Page<ProductDTO> getAllProducts(Integer pageNumber, Integer pageSize);

    /**
     * Retrieves a product by its ID.
     *
     * @param id the ID of the product
     * @return the ProductDTO object
     */
    ProductDTO getProductById(Integer id);

    /**
     * Creates a new product.
     *
     * @param productDTO the ProductDTO object containing the details of the product
     * @throws AppException if there is an error during the creation of the product
     */
    void createProduct(ProductDTO productDTO) throws AppException;

    /**
     * Updates a product with the specified ID.
     *
     * @param id         the ID of the product to update
     * @param productDTO the ProductDTO object containing the updated details
     * @throws AppException if there is an error during the update of the product
     */
    void updateProductWithId(Integer id, ProductDTO productDTO) throws AppException;

    /**
     * Deletes a product with the specified ID.
     *
     * @param id the ID of the product to delete
     */
    void deleteProductWithId(Integer id);

    /**
     * Retrieves all products with weight greater than the specified value and pagination.
     *
     * @param weight     the weight value
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing ProductDTOs
     */
    Page<ProductDTO> getAllProductsWithWeightBiggerThan(Integer weight, Integer pageNumber, Integer pageSize);

    /**
     * Retrieves the manufacturer of a product with the specified ID.
     *
     * @param id the ID of the product
     * @return the ManufacturerDTO object
     */
    ManufacturerDTO getManufacturerByProductId(Integer id);

    /**
     * Retrieves products of a manufacturer with the specified ID and pagination.
     *
     * @param id         the ID of the manufacturer
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing ProductDTOs
     * @throws AppException if the manufacturer is not found
     */
    Page<ProductDTO> getProductsByManufacturerId(Integer id, Integer pageNumber, Integer pageSize) throws AppException;

    /**
     * Retrieves products sorted by their scores and pagination.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing ProductScoreDTOs
     */
    Page<ProductScoreDTO> getProductsSortedByScore(Integer pageNumber, Integer pageSize);

    /**
     * Retrieves a Page of ProductScoreDTOs with weight filter and pagination.
     *
     * @param weight     the weight value
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing ProductScoreDTOs
     */
    Page<ProductScoreDTO> getProductScoresPage(Integer weight, Integer pageNumber, Integer pageSize);

    /**
     * Retrieves a Page of ProductScoreWithUserHandleDTOs with weight filter and pagination.
     *
     * @param weight     the weight value
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing ProductScoreWithUserHandleDTOs
     */
    Page<ProductScoreWithUserHandleDTO> getProductScoresPageWithUsers(Integer weight, Integer pageNumber, Integer pageSize);
}
