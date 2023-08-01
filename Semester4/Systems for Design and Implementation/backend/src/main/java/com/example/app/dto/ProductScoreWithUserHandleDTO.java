package com.example.app.dto;

import lombok.*;

@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode
@ToString
public class ProductScoreWithUserHandleDTO {
    /**
     * The ProductScoreDTO object representing the product score.
     */
    @Getter
    @Setter
    private ProductScoreDTO productScoreDTO;

    /**
     * The user handle associated with the product score.
     */
    @Getter
    @Setter
    private String userHandle;
}
