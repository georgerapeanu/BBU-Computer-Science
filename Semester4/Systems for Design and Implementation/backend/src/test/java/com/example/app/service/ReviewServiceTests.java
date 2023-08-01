package com.example.app.service;

import com.example.app.dto.ProductScoreDTO;
import com.example.app.dto.model.ProductDTO;
import com.example.app.model.Ids.ReviewId;
import com.example.app.model.Manufacturer;
import com.example.app.model.Product;
import com.example.app.model.Review;
import com.example.app.repository.ProductRepository;
import com.example.app.repository.ReviewRepository;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.sql.Date;
import java.util.Arrays;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.when;

@ExtendWith(MockitoExtension.class)
public class ReviewServiceTests {
    @Mock
    private ReviewRepository reviewRepository;
    @Mock
    private ProductRepository productRepository;
    private IReviewService reviewService;
    private List<Product> products;
//
//    @BeforeEach
//    void setUp() throws RuntimeException{
//        this.reviewService = new ReviewService(reviewRepository, null, productRepository);
//        Date date = Date.valueOf("2023-03-28");
//        Manufacturer manufacturer = new Manufacturer(1, "manufacturer1", "description1", date, null);
//        this.products = Arrays.asList(
//                new Product(1, "product1", "description1", date, 20.0, 1, manufacturer),
//                new Product(2, "product2", "description2", date, 21.0, 2, manufacturer),
//                new Product(3, "product3", "description3", date, 22.0, 3, manufacturer),
//                new Product(4, "product4", "description4", date, 22.0, 3, manufacturer)
//        );
//        when(productRepository.findAll()).thenReturn(products);
//        when(reviewRepository.findAll()).thenReturn(Arrays.asList(
//                new Review(new ReviewId(1, 1), null, products.get(0), 5, "", date),
//                new Review(new ReviewId(1, 2), null, products.get(1), 4, "", date),
//                new Review(new ReviewId(1, 3), null, products.get(2), 2, "", date),
//                new Review(new ReviewId(1, 2), null, products.get(1), 1, "", date),
//                new Review(new ReviewId(1, 3), null, products.get(2), 3, "", date),
//                new Review(new ReviewId(1, 3), null, products.get(2), 2, "", date),
//                new Review(new ReviewId(1, 3), null, products.get(2), 4, "", date)
//        ));
//    }
//
//    @Test
//    public void testGetSortProductsByReviews() {
//        assertEquals(Arrays.asList(
//                new ProductScoreDTO(ProductDTO.fromProduct(products.get(0)), 5.0),
//                new ProductScoreDTO(ProductDTO.fromProduct(products.get(2)), 2.75),
//                new ProductScoreDTO(ProductDTO.fromProduct(products.get(1)), 2.5),
//                new ProductScoreDTO(ProductDTO.fromProduct(products.get(3)), 0.0)
//            ),
//                this.productService.getProductsSortedByScore(0, 4)
//        );
//    }
//    @BeforeEach
//    void setUp() throws RuntimeException{
//        this.reviewService = new ReviewService(reviewRepository, null, productRepository);
//        Date date = Date.valueOf("2023-03-28");
//        Manufacturer manufacturer = new Manufacturer(1, "manufacturer1", "description1", date, null);
//        this.products = Arrays.asList(
//                new Product(1, "product1", "description1", date, 20.0, 1, manufacturer),
//                new Product(2, "product2", "description2", date, 21.0, 2, manufacturer),
//                new Product(3, "product3", "description3", date, 22.0, 3, manufacturer),
//                new Product(4, "product4", "description4", date, 22.0, 3, manufacturer)
//        );
//        when(productRepository.findAll()).thenReturn(products);
//        when(reviewRepository.findAll()).thenReturn(Arrays.asList(
//                new Review(new ReviewId(1, 1), null, products.get(0), 5, "", date),
//                new Review(new ReviewId(1, 2), null, products.get(1), 4, "", date),
//                new Review(new ReviewId(1, 3), null, products.get(2), 2, "", date),
//                new Review(new ReviewId(1, 2), null, products.get(1), 1, "", date),
//                new Review(new ReviewId(1, 3), null, products.get(2), 3, "", date),
//                new Review(new ReviewId(1, 3), null, products.get(2), 2, "", date),
//                new Review(new ReviewId(1, 3), null, products.get(2), 4, "", date)
//        ));
//    }
//
//    @Test
//    public void testGetSortProductsByReviews() {
//        assertEquals(Arrays.asList(
//                new ProductScoreDTO(ProductDTO.fromProduct(products.get(0)), 5.0),
//                new ProductScoreDTO(ProductDTO.fromProduct(products.get(2)), 2.75),
//                new ProductScoreDTO(ProductDTO.fromProduct(products.get(1)), 2.5),
//                new ProductScoreDTO(ProductDTO.fromProduct(products.get(3)), 0.0)
//            ),
//                this.productService.getProductsSortedByScore(0, 4)
//        );
//    }
}
