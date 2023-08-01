package com.example.app.dto;

import com.example.app.dto.model.UserProfileDTO;
import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@EqualsAndHashCode
@ToString
public class UserReviewCountDTO {
    /**
     * The user profile DTO associated with the review count.
     */
    @Getter
    @Setter
    UserProfileDTO userProfileDTO;

    /**
     * The number of reviews associated with the user.
     */
    @Getter
    @Setter
    Integer count;
}
