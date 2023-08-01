package com.example.app.model;

import jakarta.persistence.*;
import jakarta.validation.constraints.Min;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;

import jakarta.validation.constraints.NotBlank;
import lombok.Setter;

import java.sql.Date;
import java.util.List;

/**
 * Represents a product entity.
 */
@NoArgsConstructor
@AllArgsConstructor
@Entity
public class Product {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Getter
    @Setter
    private Integer id;
    @NotBlank(message = "Product name is mandatory")
    @Getter
    @Setter
    private String name;
    @Getter
    @Setter
    private String description;
    @Getter
    @Setter
    private Date publishDate;
    @Min(0)
    @Getter
    @Setter
    private Double price;
    @Min(0)
    @Getter
    @Setter
    private Integer weight;
    @Getter
    @Setter
    private String color;

    @OneToMany(mappedBy = "product", fetch=FetchType.LAZY)
    @Getter
    @Setter
    List<Review> reviews;
    @ManyToOne(fetch=FetchType.LAZY)
    @JoinColumn(name = "manufacturer_id", nullable = false)
    @Getter
    @Setter
    private Manufacturer manufacturer;

}
