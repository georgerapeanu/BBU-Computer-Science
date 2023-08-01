package com.example.app.dto;

import lombok.*;

@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode
@ToString
public class UserCreatedCountDTO {
    /**
     * The user handle associated with the count.
     */
    @Getter
    @Setter
    String userHandle;

    /**
     * The number of reviews created by the user.
     */
    @Getter
    @Setter
    Integer reviewCount;

    /**
     * The number of products created by the user.
     */
    @Getter
    @Setter
    Integer productCount;

    /**
     * The number of manufacturers created by the user.
     */
    @Getter
    @Setter
    Integer manufacturerCount;
}
