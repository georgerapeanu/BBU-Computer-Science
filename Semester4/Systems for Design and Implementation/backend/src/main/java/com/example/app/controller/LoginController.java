package com.example.app.controller;

import com.example.app.exceptions.AppException;
import com.example.app.model.User;
import com.example.app.service.ILoginService;
import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.Map;

/**
 * Controller class for handling login and registration operations.
 */
@RestController
@CrossOrigin(origins = "*")
@Validated
public class LoginController {

    @Autowired
    ILoginService loginService;

    /**
     * Registers a new user.
     *
     * @param user the user to be registered
     * @return a response entity with a token if registration is successful, or an error message if registration fails
     */
    @PostMapping("/register")
    ResponseEntity<Map<String, String>> register(@RequestBody @Valid User user) {
        Map<String, String> response = new HashMap<>();
        try {
            String token = loginService.register(user);
            response.put("token", token);
            return new ResponseEntity<>(response, HttpStatus.CREATED);
        } catch (AppException e) {
            response.put("error", e.getMessage());
            return new ResponseEntity<>(response, HttpStatus.BAD_REQUEST);
        }
    }

    /**
     * Activates a user account using the activation token.
     *
     * @param token the activation token
     * @return a response entity with a success message if activation is successful, or an error message if activation fails
     */
    @PostMapping("/register/{code}")
    ResponseEntity<Map<String, String>> activate(
            @PathVariable("code") String token
    ) {
        Map<String, String> response = new HashMap<>();
        try {
            loginService.activateUser(token);
            response.put("message", "Activated");
            return new ResponseEntity<>(response, HttpStatus.CREATED);
        } catch (AppException e) {
            response.put("error", e.getMessage());
            return new ResponseEntity<>(response, HttpStatus.BAD_REQUEST);
        }
    }

    /**
     * Authenticates a user and generates an authentication token.
     *
     * @param user the user credentials for authentication
     * @return a response entity with a token if authentication is successful, or an error message if authentication fails
     */
    @PostMapping("/login")
    ResponseEntity<Map<String, String>> login(@RequestBody @Valid User user) {
        Map<String, String> response = new HashMap<>();
        try {
            String token = loginService.login(user);
            response.put("token", token);
            return new ResponseEntity<>(response, HttpStatus.CREATED);
        } catch (AppException e) {
            response.put("error", e.getMessage());
            return new ResponseEntity<>(response, HttpStatus.BAD_REQUEST);
        }
    }
}
