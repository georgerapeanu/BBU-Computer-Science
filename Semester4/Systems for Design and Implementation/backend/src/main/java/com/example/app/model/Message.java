package com.example.app.model;


import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import org.hibernate.annotations.Cascade;
import org.hibernate.annotations.CascadeType;

/**
 * Represents a message entity.
 */
@NoArgsConstructor
@AllArgsConstructor
@Entity
public class Message {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Getter
    @Setter
    private Integer id;
    @Column(name = "user_handle")
    @Getter
    @Setter
    private String userHandle;
    @ManyToOne(fetch=FetchType.LAZY)
    @JoinColumn(name = "user_handle", insertable = false, updatable = false)
    @Getter
    @Setter
    private User user;
    @Getter
    @Setter
    private String message;
    @Getter
    @Setter
    private String nickname;
}
