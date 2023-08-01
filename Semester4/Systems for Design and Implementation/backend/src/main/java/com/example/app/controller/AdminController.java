package com.example.app.controller;

import com.example.app.exceptions.AppException;
import com.example.app.model.User;
import com.example.app.service.IAdminService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;


@CrossOrigin(origins = "*")
@Validated
@RestController
public class AdminController {
    @Autowired
    IAdminService adminService;

    /**
     * Handles the "drop-all" endpoint to drop all data from the database.
     *
     * @param user the authenticated user making the request
     * @return a ResponseEntity with a success message or error message if the user is unauthorized
     */
    @PostMapping("/admin/drop-all")
    public ResponseEntity<Map<String, String>> dropAll(
            @RequestAttribute("user") User user
    ) {
        Map<String, String> response = new HashMap<>();
        if (!Objects.equals(user.getUserRole().getName(), "admin")) {
            response.put("error", "Unauthorized for this endpoint");
            return new ResponseEntity<>(response, HttpStatus.UNAUTHORIZED);
        }
        adminService.dropAll();
        response.put("message", "dropped");
        return new ResponseEntity<>(response, HttpStatus.OK);
    }

    /**
     * Handles the "recreate" endpoint to recreate the database with sample data.
     *
     * @param user the authenticated user making the request
     * @return a ResponseEntity with a success message or error message if the user is unauthorized
     */
    @PostMapping("/admin/recreate")
    public ResponseEntity<Map<String, String>> recreate(
            @RequestAttribute("user") User user
    ) {
        Map<String, String> response = new HashMap<>();
        if (!Objects.equals(user.getUserRole().getName(), "admin")) {
            response.put("error", "Unauthorized for this endpoint");
            return new ResponseEntity<>(response, HttpStatus.UNAUTHORIZED);
        }
        adminService.repopulateDb();
        response.put("message", "recreated");
        return new ResponseEntity<>(response, HttpStatus.OK);
    }

    /**
     * Handles the "change-role" endpoint to change the role of a user.
     *
     * @param user        the authenticated user making the request
     * @param user_handle the handle of the user whose role should be changed
     * @param role        the new role for the user
     * @return a ResponseEntity with a success message or error message if the user is unauthorized or if the role change fails
     */
    @PostMapping("/admin/change-role")
    public ResponseEntity<Map<String, String>> changeRole(
            @RequestAttribute("user") User user,
            @RequestParam("user_handle") String user_handle,
            @RequestParam("role") String role
    ) {
        Map<String, String> response = new HashMap<>();
        if (!Objects.equals(user.getUserRole().getName(), "admin")) {
            response.put("error", "Unauthorized for this endpoint");
            return new ResponseEntity<>(response, HttpStatus.UNAUTHORIZED);
        }
        try {
            adminService.changeRole(user_handle, role);
        } catch (AppException e) {
            response.put("error", e.toString());
            return new ResponseEntity<>(response, HttpStatus.BAD_REQUEST);
        }
        return new ResponseEntity<>(response, HttpStatus.OK);
    }
}
