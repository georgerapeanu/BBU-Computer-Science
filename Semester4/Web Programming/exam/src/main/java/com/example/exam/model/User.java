package com.example.exam.model;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.OneToOne;
import jakarta.persistence.Table;
import jakarta.validation.constraints.NotNull;
import lombok.*;

@Entity
@EqualsAndHashCode
@ToString
@NoArgsConstructor
@AllArgsConstructor
@Table(name = "Users")
public class User {
    @Id
    @Getter
    @Setter
    @NotNull
    Integer id;
    @Getter
    @Setter
    String username;
    @Getter
    @Setter
    @OneToOne(mappedBy = "user")
    FamilyRelation familyRelation;

    public User(Integer id, String username) {
        this.id = id;
        this.username = username;
    }
}
