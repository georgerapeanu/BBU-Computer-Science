package com.example.app.dto.model;

import lombok.*;

/**
 * Data Transfer Object for User.
 */
@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode
@ToString
public class UserDTO {
    @Getter
    @Setter
    private String handle;
    @Getter
    @Setter
    private String password;
}
