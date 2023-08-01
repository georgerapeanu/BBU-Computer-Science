package com.example.app.controller;

import com.example.app.dto.ProductScoreWithUserHandleDTO;
import com.example.app.dto.model.ManufacturerDTO;
import com.example.app.dto.model.ProductDTO;
import com.example.app.dto.ProductScoreDTO;
import com.example.app.dto.model.ReviewDTO;
import com.example.app.exceptions.AppException;
import com.example.app.model.User;
import com.example.app.service.IManufacturerService;
import com.example.app.service.IProductService;
import com.example.app.service.IReviewService;
import com.example.app.util.JWTUtils;
import jakarta.validation.constraints.Max;
import jakarta.validation.constraints.Min;
import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import jakarta.validation.Valid;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;

/**
 * Controller class for managing products.
 */
@NoArgsConstructor
@AllArgsConstructor
@RestController
@CrossOrigin(origins = "*")
@Validated
public class ProductController {
    @Autowired
    private IProductService productService;
    @Autowired
    private IReviewService reviewService;
    @Autowired
    private IManufacturerService manufacturerService;

    /**
     * Retrieves a paginated list of products.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @param user       the user making the request
     * @return a ResponseEntity containing the paginated list of products
     */
    @GetMapping(path="/products")
    public @ResponseBody ResponseEntity<Page<ProductDTO>> getProducts(
            @RequestParam
            Integer pageNumber,
            @RequestParam
            @Min(value=4, message = "pageSize should be at least 4")
            @Max(value=10, message = "pageSize should be at most 10")
            Integer pageSize,
            @RequestAttribute("User") User user
    ){
        if(!user.getUserRole().getRead_all()){
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        return new ResponseEntity<>(productService.getAllProducts( pageNumber, pageSize), HttpStatus.OK);
    }

    /**
     * Retrieves a product by its ID.
     *
     * @param id   the product ID
     * @param user the user making the request
     * @return a ResponseEntity containing the product
     */
    @GetMapping(path="/products/{id}", produces = "application/json")
    public @ResponseBody ResponseEntity<ProductDTO> getProduct(
            @PathVariable("id") Integer id,
            @RequestAttribute("user") User user
        ) {
        ProductDTO productDTO = productService.getProductById(id);
        if(productDTO == null){
            return new ResponseEntity<>(null, HttpStatus.NOT_FOUND);
        } else {
            try {
                ManufacturerDTO manufacturerDTO = manufacturerService.getManufacturerById(productDTO.getManufacturerId());
                if(!user.getUserRole().getRead_all() && (!user.getUserRole().getRead_own() || !Objects.equals(manufacturerDTO.getUserHandle(), user.getHandle()))) {
                    return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
                }
            } catch (AppException e) {
                throw new RuntimeException(e);
            }

            return new ResponseEntity<>(productDTO, HttpStatus.OK);
        }
    }

    /**
     * Retrieves the manufacturer of a product.
     *
     * @param id   the product ID
     * @param user the user making the request
     * @return a ResponseEntity containing the manufacturer
     */
    @GetMapping(path="/products/{id}/manufacturer", produces = "application/json")
    public @ResponseBody ResponseEntity<ManufacturerDTO> getProductManufacturer(
            @PathVariable("id") Integer id,
            @RequestAttribute("user") User user
    ) {
        ManufacturerDTO manufacturerDTO = productService.getManufacturerByProductId(id);
        if(manufacturerDTO == null){
            return new ResponseEntity<>(null, HttpStatus.NOT_FOUND);
        } else {
            if(!user.getUserRole().getRead_all() && (!user.getUserRole().getRead_own() || !Objects.equals(manufacturerDTO.getUserHandle(), user.getHandle()))) {
                return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
            }
             return new ResponseEntity<>(manufacturerDTO, HttpStatus.OK);
        }
    }

    /**
     * Creates a new product.
     *
     * @param productDTO the product to create
     * @param user       the user making the request
     * @return a ResponseEntity indicating the result of the operation
     */
    @PostMapping(path="/products", produces = "application/json")
    public ResponseEntity<Map<String, String>> createProduct(
            @Valid @RequestBody ProductDTO productDTO,
            @RequestAttribute("user") User user
    ) {
        Map<String, String> response = new HashMap<>();

        if(!user.getUserRole().getCreate()) {
            response.put("message", "Unauthorized to create resource");
            return new ResponseEntity<>(response, HttpStatus.UNAUTHORIZED);
        }

        try {
            ManufacturerDTO manufacturerDTO = manufacturerService.getManufacturerById(productDTO.getManufacturerId());
            if(!Objects.equals(manufacturerDTO.getUserHandle(), user.getHandle())) {
                throw new AppException("Manufacturer doesn't match user");
            }
            productService.createProduct(productDTO);
            response.put("message", "Product created");
            return new ResponseEntity<>(response, HttpStatus.OK);
        } catch (AppException e) {
            response.put("error", e.getMessage());
            return new ResponseEntity<>(response, HttpStatus.BAD_REQUEST);
        }
    }

    /**
     * Updates an existing product.
     *
     * @param id         the ID of the product to update
     * @param productDTO the updated product data
     * @param user       the user making the request
     * @return a ResponseEntity indicating the result of the operation
     */
    @PatchMapping(path="/products/{id}", produces = "application/json")
    public @ResponseBody ResponseEntity<Map<String, String>> updateProduct(
            @PathVariable("id") Integer id,
            @Valid @RequestBody ProductDTO productDTO,
            @RequestAttribute("user") User user
    ) {
        Map<String, String> response = new HashMap<>();
        try {
            ProductDTO oldProductDTO = productService.getProductById(id);
            if(oldProductDTO == null) {
                throw new AppException("No product with such id exists");
            }
            if(!user.getUserRole().getUpdate_all()) {
                ManufacturerDTO oldManufacturerDTO = manufacturerService.getManufacturerById(oldProductDTO.getManufacturerId());
                ManufacturerDTO manufacturerDTO = manufacturerService.getManufacturerById(productDTO.getManufacturerId());
                if(!Objects.equals(manufacturerDTO.getUserHandle(), user.getHandle())) {
                    throw new AppException("Manufacturer doesn't match user");
                }
                if(!Objects.equals(oldManufacturerDTO.getUserHandle(), manufacturerDTO.getUserHandle())){
                    response.put("error", "Unauthorized to transfer resource between users");
                    return new ResponseEntity<>(response, HttpStatus.UNAUTHORIZED);
                }
            }

            productService.updateProductWithId(id, productDTO);
            response.put("message", "Product updated");
            return new ResponseEntity<>(response, HttpStatus.OK);
        } catch (AppException e) {
            response.put("error", e.getMessage());
            return new ResponseEntity<>(response, HttpStatus.BAD_REQUEST);
        }
    }

    /**
     * Deletes a product.
     *
     * @param id   the ID of the product to delete
     * @param user the user making the request
     * @return a ResponseEntity indicating the result of the operation
     */
    @DeleteMapping(path="/products/{id}", produces = "application/json")
    public @ResponseBody ResponseEntity<Map<String, String>> deleteProduct(
            @PathVariable("id") Integer id,
            @RequestAttribute("user") User user
    ) {
        Map<String, String> response = new HashMap<>();
        ProductDTO productDTO = productService.getProductById(id);
        try {
            ManufacturerDTO manufacturerDTO = manufacturerService.getManufacturerById(productDTO.getManufacturerId());
            if(!user.getUserRole().getDelete_all() && (!user.getUserRole().getDelete_own() || !Objects.equals(manufacturerDTO.getUserHandle(), user.getHandle()))) {
                response.put("error", "Unauthorized to delete resource");
                return new ResponseEntity<>(response, HttpStatus.UNAUTHORIZED);
            }
        } catch (AppException e) {
            throw new RuntimeException(e);
        }
        productService.deleteProductWithId(id);
        response.put("message", "Product deleted");
        return new ResponseEntity<>(response, HttpStatus.OK);
    }

    /**
     * Retrieves all products with weight bigger than the specified value.
     *
     * @param weight     the minimum weight value
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @param user       the user making the request
     * @return a ResponseEntity containing the list of products
     */
    @GetMapping(path="/products/weight-filter", produces = "application/json")
    public @ResponseBody ResponseEntity<Page<ProductDTO>> getAllProductsWithWeightBiggerThan(
            @RequestParam Integer weight,
            @RequestParam
            Integer pageNumber,
            @RequestParam
            @Min(value=4, message = "pageSize should be at least 4")
            @Max(value=10, message = "pageSize should be at most 10")
            Integer pageSize,
            @RequestAttribute("user") User user
    ) {
        if(!user.getUserRole().getRead_all()) {
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        return new ResponseEntity<>(productService.getAllProductsWithWeightBiggerThan(weight, pageNumber, pageSize), HttpStatus.OK);
    }

    /**
     * Retrieves all products sorted by reviews.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @param user       the user making the request
     * @return a ResponseEntity containing the list of products with their scores
     */
    @GetMapping(path="/products/sorted-by-reviews", produces = "application/json")
    public @ResponseBody ResponseEntity<Page<ProductScoreDTO>> getAllProductsSortedByReviews(
            @RequestParam
            Integer pageNumber,
            @RequestParam
            @Min(value=4, message = "pageSize should be at least 4")
            @Max(value=10, message = "pageSize should be at most 10")
            Integer pageSize,
            @RequestAttribute("user") User user
    ){
        if(!user.getUserRole().getRead_all()) {
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        return new ResponseEntity<>(productService.getProductsSortedByScore(pageNumber, pageSize), HttpStatus.OK);
    }

    /**
     * Retrieves the reviews for a product.
     *
     * @param id         the ID of the product
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @param user       the user making the request
     * @return a ResponseEntity containing the list of reviews
     */
    @GetMapping(path="/products/{id}/reviews", produces = "application/json")
    public @ResponseBody ResponseEntity<Page<ReviewDTO>> getReviews(
            @PathVariable("id") Integer id,
            @RequestParam
            Integer pageNumber,
            @RequestParam
            @Min(value=4, message = "pageSize should be at least 4")
            @Max(value=10, message = "pageSize should be at most 10")
            Integer pageSize,
            @RequestAttribute("user") User user
    ) {
        try {
            ProductDTO productDTO = productService.getProductById(id);
            if(productDTO == null) {
                throw new AppException("Product with such id not found");
            }
            ManufacturerDTO manufacturerDTO = manufacturerService.getManufacturerById(productDTO.getManufacturerId());
            if(manufacturerDTO == null) {
                throw new RuntimeException("Manufacturer is empty");
            }
            if(!user.getUserRole().getRead_all() && (!user.getUserRole().getRead_own() || !Objects.equals(user.getHandle(), manufacturerDTO.getUserHandle()))) {
                return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
            }
            return new ResponseEntity<>(reviewService.getReviewsForProduct(id, pageNumber, pageSize), HttpStatus.OK);
        } catch (AppException e) {
            return new ResponseEntity<>(null, HttpStatus.BAD_REQUEST);
        }
    }

    /**
     * Retrieves a page of product scores.
     *
     * @param weight     the minimum weight value
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @param user       the user making the request
     * @return a ResponseEntity containing the page of product scores
     */
    @GetMapping(path="/product-scores")
    public @ResponseBody ResponseEntity<Page<ProductScoreDTO>> getProductScoresPage(
            @RequestParam Integer weight,
            @RequestParam
            Integer pageNumber,
            @RequestParam
            @Min(value=4, message = "pageSize should be at least 4")
            @Max(value=10, message = "pageSize should be at most 10")
            Integer pageSize,
            @RequestAttribute("user") User user
    ){
        if(!user.getUserRole().getRead_all()) {
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        return new ResponseEntity<>(productService.getProductScoresPage(weight, pageNumber, pageSize), HttpStatus.OK);
    }

    /**
     * Retrieves a page of product scores with associated user handles.
     *
     * @param weight     the minimum weight value
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @param user       the user making the request
     * @return a ResponseEntity containing the page of product scores with user handles
     */
    @GetMapping(path="/product-scores-with-users")
    public @ResponseBody ResponseEntity<Page<ProductScoreWithUserHandleDTO>> getProductScoresWithUsersPage(
            @RequestParam Integer weight,
            @RequestParam
            Integer pageNumber,
            @RequestParam
            @Min(value=4, message = "pageSize should be at least 4")
            @Max(value=10, message = "pageSize should be at most 10")
            Integer pageSize,
            @RequestAttribute("user") User user
    ){
        if(!user.getUserRole().getRead_all()) {
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        return new ResponseEntity<>(productService.getProductScoresPageWithUsers(weight, pageNumber, pageSize), HttpStatus.OK);
    }
}
