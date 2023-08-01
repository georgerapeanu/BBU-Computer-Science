package com.example.app.model;

import jakarta.persistence.*;
import jakarta.validation.constraints.NotBlank;
import lombok.*;

import java.util.List;

/**
 * Represents a user entity.
 */
@AllArgsConstructor
@NoArgsConstructor
@Entity
@EqualsAndHashCode
@ToString
public class User {
    @Id
    @Getter
    @Setter
    @NotBlank
    private String handle;

    @Getter
    @Setter
    @NotBlank
    private String password;


    @Getter
    @Setter
    private boolean activated;

    @OneToMany(mappedBy = "user", fetch = FetchType.LAZY)
    @ToString.Exclude
    List<Review> reviews;

    @Getter
    @Setter
    @OneToOne(fetch = FetchType.LAZY, mappedBy="user")
    UserProfile userProfile;


    @Getter
    @Setter
    private String role;

    @Getter
    @Setter
    @ManyToOne(fetch = FetchType.EAGER)
    @JoinColumn(name="role", insertable = false, updatable = false)
    Role userRole;

    @Getter
    @Setter
    @OneToOne(mappedBy="user", fetch=FetchType.LAZY)
    UserPreference userPreference;
}
