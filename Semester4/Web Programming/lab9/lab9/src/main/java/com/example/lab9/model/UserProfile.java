package com.example.lab9.model;

import jakarta.persistence.*;
import lombok.*;

import java.sql.Date;
import java.time.Duration;
import java.time.LocalDate;
import java.time.Period;

@AllArgsConstructor
@NoArgsConstructor
@Entity
@ToString
@Table(name="UserProfile")
public class UserProfile {
    @Getter
    @Setter
    String name;
    @Getter
    @Setter
    String email;
    @Getter
    @Setter
    String imageLink;
    @Getter
    @Setter
    Date dateOfBirth;
    @Getter
    @Setter
    String home;
    @ToString.Exclude
    @Getter
    @Setter
    @OneToOne
    @JoinColumn(name="username", referencedColumnName = "username", insertable = false, updatable = false)
    User user;
    @Id
    @Getter
    @Setter
    String username;

    public Integer getAge() {
        if(dateOfBirth == null) {
            return null;
        }
        return Period.between(dateOfBirth.toLocalDate(), LocalDate.now()).getYears();
    }
}
