package com.example.app.dto.model;

import com.example.app.model.UserProfile;
import jakarta.validation.constraints.NotBlank;
import lombok.*;

import java.sql.Date;

/**
 * Data Transfer Object for UserProfile.
 */
@EqualsAndHashCode
@ToString
@NoArgsConstructor
@AllArgsConstructor
public class UserProfileDTO {
    @NotBlank
    @Getter
    @Setter
    private String name;
    @Getter
    @Setter
    private String handle;
    @Getter
    @Setter
    private String email;
    @Getter
    @Setter
    private Date birthday;
    @Getter
    @Setter
    private Date registeredAt;

    /**
     * Converts UserProfile to UserProfileDTO object.
     *
     * @param userProfile The UserProfile object to convert.
     * @return The converted UserProfileDTO object.
     */
    public static UserProfileDTO fromUserProfile(UserProfile userProfile) {
        return new UserProfileDTO(
                userProfile.getName(),
                userProfile.getHandle(),
                userProfile.getEmail(),
                userProfile.getBirthday(),
                userProfile.getRegisteredAt()
        );
    }

    /**
     * Converts UserProfileDTO to UserProfile object.
     *
     * @param userProfileDTO The UserProfileDTO object to convert.
     * @return The converted UserProfile object.
     */
    public static UserProfile toUserProfile(UserProfileDTO userProfileDTO) {
        UserProfile userProfile = new UserProfile();
        userProfile.setName(userProfileDTO.getName());
        userProfile.setHandle(userProfileDTO.getHandle());
        userProfile.setEmail(userProfileDTO.getEmail());
        userProfile.setBirthday(userProfileDTO.getBirthday());
        userProfile.setRegisteredAt(userProfileDTO.getRegisteredAt());
        return userProfile;
    }
}
