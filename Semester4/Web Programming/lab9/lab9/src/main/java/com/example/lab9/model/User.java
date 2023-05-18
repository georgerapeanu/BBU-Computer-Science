package com.example.lab9.model;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.OneToOne;
import jakarta.persistence.Table;
import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@Entity
@ToString
@Table(name="User")
public class User {
    @Getter
    @Setter
    @Id
    String username;
    @Getter
    @Setter
    String password;
    @ToString.Exclude
    @Getter
    @Setter
    @OneToOne(mappedBy = "user")
    UserProfile userProfile;
}
