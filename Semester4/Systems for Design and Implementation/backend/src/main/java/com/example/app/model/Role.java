package com.example.app.model;

import jakarta.persistence.*;
import lombok.*;

import java.util.List;

/**
 * Represents a role entity.
 */
@Entity
@NoArgsConstructor
@AllArgsConstructor
@ToString
@EqualsAndHashCode
public class Role {
    @Getter
    @Setter
    @Id
    private String name;
    @Getter
    @Setter
    private Boolean read_all;
    @Getter
    @Setter
    private Boolean update_all;
    @Getter
    @Setter
    private Boolean delete_all;
    @Getter
    @Setter
    private Boolean read_own;
    @Getter
    @Setter
    private Boolean update_own;
    @Getter
    @Setter
    private Boolean delete_own;
    @Getter
    @Setter
    private Boolean create;
}
