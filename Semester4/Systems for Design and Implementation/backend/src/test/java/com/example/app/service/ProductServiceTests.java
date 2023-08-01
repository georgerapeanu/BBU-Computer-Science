package com.example.app.service;


import com.example.app.dto.ManufacturerProductCountDTO;
import com.example.app.dto.model.ManufacturerDTO;
import com.example.app.model.Manufacturer;
import com.example.app.model.Product;
import com.example.app.repository.ManufacturerRepository;
import com.example.app.repository.ProductRepository;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.sql.Date;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.when;

@ExtendWith(MockitoExtension.class)
public class ProductServiceTests {
    @Mock
    private ManufacturerRepository manufacturerRepository;
    @Mock
    private ProductRepository productRepository;
    private IProductService productService;
    private List<Product> products;
    private List<Manufacturer> manufacturers;

//    @BeforeEach
//    void setUp() throws RuntimeException{
//        this.productService = new ProductService(productRepository, manufacturerRepository);
//        Date date = Date.valueOf("2023-03-28");
//        this.manufacturers = Arrays.asList(
//                new Manufacturer(1, "manufacturer1", "description1", date, new ArrayList<>()),
//                new Manufacturer(2, "manufacturer2", "description2", date, new ArrayList<>()),
//                new Manufacturer(3, "manufacturer3", "description3", date, new ArrayList<>())
//        );
//        this.products = Arrays.asList(
//                new Product(1, "product1", "description1", date, 20.0, 1, manufacturers.get(0)),
//                new Product(2, "product2", "description2", date, 21.0, 2, manufacturers.get(1)),
//                new Product(3, "product3", "description3", date, 22.0, 3, manufacturers.get(1)),
//                new Product(4, "product4", "description4", date, 22.0, 3, manufacturers.get(1))
//        );
//        when(productRepository.findAll()).thenReturn(products);
//        when(manufacturerRepository.findAll()).thenReturn(manufacturers);
//    }
//
//    @Test
//    public void testGetManufacturerByProductId() {
//        assertEquals(Arrays.asList(
//                        new ManufacturerProductCountDTO(ManufacturerDTO.fromManufacturer(manufacturers.get(1)), 3),
//                        new ManufacturerProductCountDTO(ManufacturerDTO.fromManufacturer(manufacturers.get(0)), 1),
//                        new ManufacturerProductCountDTO(ManufacturerDTO.fromManufacturer(manufacturers.get(2)), 0)
//                ),
//                this.productService.getManufacturersSortedByProducts()
//        );
//    }
}
