package com.example.app.model;


import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.OneToOne;
import lombok.*;

/**
 * Represents a UserPreference entity.
 */
@Entity
@NoArgsConstructor
@AllArgsConstructor
@ToString
@EqualsAndHashCode
public class UserPreference {
    @Getter
    @Setter
    @Id
    String handle;
    @Getter
    @Setter
    Integer page_size;
    @Getter
    @Setter
    @OneToOne
    @JoinColumn(name="handle", insertable = false, updatable = false)
    User user;
}
