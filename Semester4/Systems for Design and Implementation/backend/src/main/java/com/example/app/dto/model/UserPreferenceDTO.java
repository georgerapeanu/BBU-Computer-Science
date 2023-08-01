package com.example.app.dto.model;

import com.example.app.model.User;
import com.example.app.model.UserPreference;
import lombok.*;

/**
 * Data Transfer Object for UserPreference.
 */
@ToString
@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode
public class UserPreferenceDTO {
    @Getter
    @Setter
    private String handle;
    @Getter
    @Setter
    private Integer page_size;

    /**
     * Converts UserPreferenceDTO to UserPreference object.
     *
     * @param preference The UserPreferenceDTO object to convert.
     * @param user       The User object associated with the preference.
     * @return The converted UserPreference object.
     */
    public static UserPreference toUserPreference(UserPreferenceDTO preference, User user) {
        return new UserPreference(preference.getHandle(), preference.getPage_size(), user);
    }

    /**
     * Converts UserPreference to UserPreferenceDTO object.
     *
     * @param preference The UserPreference object to convert.
     * @return The converted UserPreferenceDTO object.
     */
    public static UserPreferenceDTO fromUserPreference(UserPreference preference) {
        return new UserPreferenceDTO(preference.getHandle(), preference.getPage_size());
    }
}
