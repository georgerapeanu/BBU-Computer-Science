package com.example.app.dto.model;

import com.example.app.model.Manufacturer;
import com.example.app.model.User;
import jakarta.validation.constraints.NotBlank;
import lombok.*;

import java.sql.Date;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

/**
 * Data Transfer Object for Manufacturer.
 */
@AllArgsConstructor
@EqualsAndHashCode
@ToString
public class ManufacturerDTO {
    @Getter
    @Setter
    private Integer id;

    @Getter
    @Setter
    @NotBlank
    private String name;

    @Getter
    @Setter
    @NotBlank
    private String description;

    @Getter
    @Setter
    private Date registerDate;

    @Getter
    @Setter
    private String userHandle;

    /**
     * Creates a ManufacturerDTO object from a Manufacturer entity.
     *
     * @param manufacturer the Manufacturer entity
     * @return the ManufacturerDTO object
     */
    public static ManufacturerDTO fromManufacturer(Manufacturer manufacturer) {
        return new ManufacturerDTO(
                manufacturer.getId(),
                manufacturer.getName(),
                manufacturer.getDescription(),
                manufacturer.getRegisterDate(),
                manufacturer.getUserHandle()
        );
    }

    /**
     * Converts a ManufacturerDTO object to a Manufacturer entity.
     *
     * @param manufacturerDTO the ManufacturerDTO object
     * @param user            the User entity
     * @return the Manufacturer entity
     */
    public static Manufacturer toManufacturer(ManufacturerDTO manufacturerDTO, User user) {
        Manufacturer manufacturer = new Manufacturer();
        manufacturer.setId(manufacturer.getId());
        manufacturer.setDescription(manufacturerDTO.getDescription());
        manufacturer.setName(manufacturerDTO.getName());
        manufacturer.setRegisterDate(manufacturerDTO.getRegisterDate());
        manufacturer.setUser(user);
        manufacturer.setUserHandle(manufacturerDTO.getUserHandle());
        return manufacturer;
    }
}
