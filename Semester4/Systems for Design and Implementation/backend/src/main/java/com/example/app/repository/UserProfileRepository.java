package com.example.app.repository;

import com.example.app.model.UserProfile;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

/**
 * Repository interface for managing UserProfiles.
 */
@Repository
public interface UserProfileRepository
        extends JpaRepository<UserProfile, String>,
        JpaSpecificationExecutor<UserProfile>{
}