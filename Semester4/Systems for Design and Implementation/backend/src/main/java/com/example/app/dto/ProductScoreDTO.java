package com.example.app.dto;

import com.example.app.dto.model.ProductDTO;
import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@EqualsAndHashCode
@ToString
public class ProductScoreDTO {
    /**
     * The ProductDTO object representing the product.
     */
    @Getter
    @Setter
    private ProductDTO productDTO;

    /**
     * The score associated with the product.
     */
    @Getter
    @Setter
    private Double score;
}
