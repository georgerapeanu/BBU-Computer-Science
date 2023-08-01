package com.example.app.repository;

import com.example.app.model.Message;
import com.example.app.model.User;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

/**
 * Repository interface for managing messages.
 */
public interface MessageRepository extends JpaRepository<Message, Integer> {
    List<Message> findAllByUserHandleOrderById(String user_handle);
    List<Message> findFirst4ByOrderByIdDesc();
}
