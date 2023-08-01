package com.example.app.dto;

import com.example.app.dto.model.ManufacturerDTO;
import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@EqualsAndHashCode
@ToString
public class ManufacturerProductCountDTO {
    /**
     * The ManufacturerDTO object representing the manufacturer.
     */
    @Getter
    @Setter
    ManufacturerDTO manufacturerDTO;

    /**
     * The count of products associated with the manufacturer.
     */
    @Getter
    @Setter
    Integer productCount;
}
