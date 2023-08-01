package com.example.app.repository;

import com.example.app.model.UserPreference;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

/**
 * Repository interface for managing user preferences.
 */
@Repository
public interface UserPreferenceRepository extends JpaRepository<UserPreference, String> {
}
