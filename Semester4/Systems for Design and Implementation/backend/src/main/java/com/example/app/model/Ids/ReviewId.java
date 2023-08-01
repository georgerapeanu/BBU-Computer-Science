package com.example.app.model.Ids;

import jakarta.persistence.Column;
import jakarta.persistence.Embeddable;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.util.Objects;

/**
 * Composite primary key class for the Review entity.
 */
@Embeddable
@AllArgsConstructor
@NoArgsConstructor
public class ReviewId implements Serializable {
    @Column(name = "user_handle")
    public String userHandle;
    @Column(name = "product_id")
    public Integer productId;

    /**
     * Get the user handle.
     *
     * @return the user handle
     */
    public String getUserHandle() {
        return userHandle;
    }

    /**
     * Set the user handle.
     *
     * @param userHandle the user handle to set
     */
    public void setUserHandle(String userHandle) {
        this.userHandle = userHandle;
    }

    /**
     * Get the product ID.
     *
     * @return the product ID
     */
    public Integer getProductId() {
        return productId;
    }

    /**
     * Set the product ID.
     *
     * @param productId the product ID to set
     */
    public void setProductId(Integer productId) {
        this.productId = productId;
    }

    /**
     * Checks if the current object is equal to another object.
     *
     * @param o the other object to compare
     * @return true if the objects are equal, false otherwise
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ReviewId reviewId = (ReviewId) o;
        return Objects.equals(userHandle, reviewId.userHandle) && Objects.equals(productId, reviewId.productId);
    }

    /**
     * Generates the hash code for the object.
     *
     * @return the hash code
     */
    @Override
    public int hashCode() {
        return Objects.hash(userHandle, productId);
    }
}
