package com.example.app.service;

import com.example.app.dto.ProductScoreDTO;
import com.example.app.dto.ProductScoreWithUserHandleDTO;
import com.example.app.exceptions.AppException;
import com.example.app.model.Manufacturer;
import com.example.app.model.Product;
import com.example.app.dto.model.ManufacturerDTO;
import com.example.app.dto.model.ProductDTO;
import com.example.app.repository.ManufacturerRepository;
import com.example.app.repository.ProductRepository;
import com.example.app.repository.specification.ProductSpecifications;
import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageImpl;
import org.springframework.data.domain.PageRequest;
import org.springframework.stereotype.Service;

import java.util.Objects;
import java.util.Optional;

/**
 * The product service implementation.
 */
@NoArgsConstructor
@AllArgsConstructor
@Service
public class ProductService implements IProductService {

    @Autowired
    ProductRepository productRepository;

    @Autowired
    ManufacturerRepository manufacturerRepository;

    /**
     * Retrieves all products with pagination.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing the list of ProductDTOs
     */
    public Page<ProductDTO> getAllProducts(Integer pageNumber, Integer pageSize) {
        return productRepository
                .findAll(PageRequest.of(pageNumber, pageSize))
                .map(ProductDTO::fromProduct);
    }

    /**
     * Retrieves a product by its ID.
     *
     * @param id the product ID
     * @return the ProductDTO object
     */
    public ProductDTO getProductById(Integer id) {
        Product product = productRepository.findById(id).orElse(null);
        if (product == null) {
            return null;
        }
        return ProductDTO.fromProduct(product);
    }

    /**
     * Creates a new product.
     *
     * @param productDTO the ProductDTO object containing the product details
     * @throws AppException if the manufacturer is not found
     */
    public void createProduct(ProductDTO productDTO) throws AppException {
        Optional<Manufacturer> manufacturer = manufacturerRepository.findById(productDTO.getManufacturerId());
        if (manufacturer.isEmpty()) {
            throw new AppException("Manufacturer not found");
        }

        productRepository.save(ProductDTO.toProduct(productDTO, manufacturer.get()));
    }

    /**
     * Updates a product with the specified ID.
     *
     * @param id          the product ID
     * @param productDTO  the ProductDTO object containing the updated product details
     * @throws AppException if no product with the specified ID is found or the manufacturer is not found
     */
    public void updateProductWithId(Integer id, ProductDTO productDTO) throws AppException {
        Product repoProduct = productRepository.findById(id).orElse(null);
        if (repoProduct == null) {
            throw new AppException("No such product exists");
        }
        Manufacturer manufacturer = manufacturerRepository.findById(productDTO.getManufacturerId()).orElse(null);
        if (manufacturer == null) {
            throw new AppException("No such manufacturer exists");
        }
        Product product = ProductDTO.toProduct(productDTO, manufacturer);
        product.setId(repoProduct.getId());
        productRepository.save(product);
    }

    /**
     * Deletes a product with the specified ID.
     *
     * @param id the product ID
     */
    public void deleteProductWithId(Integer id) {
        productRepository.deleteById(id);
    }

    /**
     * Retrieves all products with weight bigger than the specified value and pagination.
     *
     * @param weight     the weight threshold
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing the list of ProductDTOs
     */
    public Page<ProductDTO> getAllProductsWithWeightBiggerThan(Integer weight, Integer pageNumber, Integer pageSize) {
        return productRepository
                .findAll(ProductSpecifications.weightBiggerThan(weight), PageRequest.of(pageNumber, pageSize))
                .map(ProductDTO::fromProduct);
    }

    /**
     * Retrieves the manufacturer of a product by its ID.
     *
     * @param id the product ID
     * @return the ManufacturerDTO object
     */
    @Override
    public ManufacturerDTO getManufacturerByProductId(Integer id) {
        Product product = productRepository.findById(id).orElse(null);
        if (product == null) {
            return null;
        }
        return ManufacturerDTO.fromManufacturer(product.getManufacturer());
    }

    /**
     * Retrieves a page of products by the manufacturer ID.
     *
     * @param id          the manufacturer ID
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing the list of ProductDTOs
     * @throws AppException if no manufacturer with the specified ID is found
     */
    @Override
    public Page<ProductDTO> getProductsByManufacturerId(Integer id, Integer pageNumber, Integer pageSize) throws AppException {
        Manufacturer manufacturer = manufacturerRepository.findById(id).orElse(null);
        if (manufacturer == null) {
            throw new AppException("No such manufacturer exists");
        }
        return productRepository
                .findAllByManufacturer(manufacturer, PageRequest.of(pageNumber, pageSize))
                .map(ProductDTO::fromProduct);
    }

    /**
     * Retrieves a page of products sorted by their average score.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing the list of ProductScoreDTOs
     */
    @Override
    public Page<ProductScoreDTO> getProductsSortedByScore(Integer pageNumber, Integer pageSize) {
        return productRepository
                .getProductsSortedByAverageScore(PageRequest.of(pageNumber, pageSize));
    }

    /**
     * Retrieves a page of product scores filtered by weight and pagination.
     *
     * @param weight     the weight threshold
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing the list of ProductScoreDTOs
     */
    @Override
    public Page<ProductScoreDTO> getProductScoresPage(Integer weight, Integer pageNumber, Integer pageSize) {
        Page<ProductDTO> productDTOPage = productRepository
                .findAll(ProductSpecifications.weightBiggerThan(weight), PageRequest.of(pageNumber, pageSize))
                .map(ProductDTO::fromProduct);
        return new PageImpl<>(
                productRepository.getProductScoresFromList(productDTOPage.getContent()),
                PageRequest.of(pageNumber, pageSize),
                productDTOPage.getTotalElements()
        );
    }

    /**
     * Retrieves a page of product scores with the associated user handle, filtered by weight and pagination.
     *
     * @param weight     the weight threshold
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing the list of ProductScoreWithUserHandleDTOs
     */
    @Override
    public Page<ProductScoreWithUserHandleDTO> getProductScoresPageWithUsers(Integer weight, Integer pageNumber, Integer pageSize) {
        return this.getProductScoresPage(weight, pageNumber, pageSize)
                .map(productScoreDTO -> {
                    return new ProductScoreWithUserHandleDTO(
                            productScoreDTO,
                            manufacturerRepository.findById(productScoreDTO.getProductDTO().getManufacturerId()).get().getUserHandle()
                    );
                });
    }
}
