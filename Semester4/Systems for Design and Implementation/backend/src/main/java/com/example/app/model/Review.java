package com.example.app.model;

import com.example.app.model.Ids.ReviewId;
import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.sql.Date;

/**
 * Represents a review entity.
 */
@NoArgsConstructor
@AllArgsConstructor
@Entity
public class Review {

    @EmbeddedId
    @Getter
    @Setter
    ReviewId id = new ReviewId();
    @MapsId("userHandle")
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name="user_handle", nullable=false)
    @Getter
    @Setter
    private User user;

    @MapsId("productId")
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name="product_id", nullable=false)
    @Getter
    @Setter
    private Product product;
    @Getter
    @Setter
    private Integer score;
    @Getter
    @Setter
    private String comment;
    @Getter
    @Setter
    private Date postedDate;
}
