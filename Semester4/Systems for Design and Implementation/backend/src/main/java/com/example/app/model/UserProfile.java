package com.example.app.model;



import jakarta.persistence.*;

import jakarta.validation.constraints.NotBlank;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.sql.Date;
import java.util.List;

/**
 * Represents a user profile entity.
 */
@Entity
@Table(name="user_profile")
@NoArgsConstructor
@AllArgsConstructor
public class UserProfile {
    @NotBlank(message = "User name is mandatory")
    @Getter
    @Setter
    private String name;
    @Id
    @Getter
    @Setter
    @NotBlank(message = "Handle is mandatory")
    private String handle;
    @Getter
    @Setter
    @NotBlank(message = "Email is mandatory")
    private String email;
    @Getter
    @Setter
    private Date birthday;
    @Getter
    @Setter
    private Date registeredAt;

    @OneToOne(fetch = FetchType.LAZY, cascade = CascadeType.ALL)
    @Getter
    @Setter
    @JoinColumn(name = "handle")
    private User user;
}
