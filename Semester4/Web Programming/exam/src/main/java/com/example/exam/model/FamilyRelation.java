package com.example.exam.model;

import jakarta.persistence.*;
import lombok.*;

@Entity
@EqualsAndHashCode
@ToString
@NoArgsConstructor
@AllArgsConstructor
@Table(name = "FamilyRelations")
public class FamilyRelation {
    @Id
    @Getter
    @Setter
    Integer id;
    @Getter
    @Setter
    @OneToOne
    @JoinColumn(name="userId", referencedColumnName = "id", insertable = false, updatable = false)
    User user;
    @Getter
    @Setter
    Integer userId;
    @Getter
    @Setter
    String mother;
    @Getter
    @Setter
    String father;
}
