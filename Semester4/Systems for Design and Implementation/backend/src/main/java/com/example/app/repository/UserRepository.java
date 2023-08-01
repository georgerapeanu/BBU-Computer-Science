package com.example.app.repository;

import com.example.app.model.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

/**
 * Repository interface for managing users.
 */
@Repository
public interface UserRepository
        extends JpaRepository<User, String>,
                JpaSpecificationExecutor<User>,
                IUserRepository{
}
