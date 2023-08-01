package com.example.app.controller;

import com.example.app.dto.ManufacturerProductCountDTO;
import com.example.app.dto.model.ManufacturerDTO;
import com.example.app.dto.model.ProductDTO;
import com.example.app.exceptions.AppException;
import com.example.app.model.User;
import com.example.app.service.IManufacturerService;
import com.example.app.service.IProductService;
import com.example.app.util.JWTUtils;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.validation.Valid;
import jakarta.validation.constraints.Max;
import jakarta.validation.constraints.Min;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;

/**
 * Controller class for handling manufacturer-related operations.
 */
@RestController
@Validated
@CrossOrigin(origins = "*")
public class ManufacturerController {
    @Autowired
    private IManufacturerService manufacturerService;
    @Autowired
    private IProductService productService;

    /**
     * Retrieves a page of manufacturers.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @param user       the user making the request
     * @return a response entity containing a page of manufacturers if the user is authorized, or an unauthorized status if not authorized
     */
    @GetMapping(path = "/manufacturers")
    public @ResponseBody
    ResponseEntity<Page<ManufacturerDTO>> getManufacturers(
            @RequestParam
            Integer pageNumber,
            @RequestParam
            @Min(value = 4, message = "pageSize should be at least 4")
            @Max(value = 10, message = "pageSize should be at most 10")
            Integer pageSize,
            @RequestAttribute("user")
            User user
    ) {
        if (!user.getUserRole().getRead_all()) {
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        return new ResponseEntity<>(manufacturerService.getAllManufacturers(pageNumber, pageSize), HttpStatus.OK);
    }

    /**
     * Retrieves a page of manufacturers sorted by the number of products they have.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @param user       the user making the request
     * @return a response entity containing a page of manufacturers sorted by product count if the user is authorized, or an unauthorized status if not authorized
     */
    @GetMapping(path = "/manufacturers/sorted-by-products")
    public @ResponseBody
    ResponseEntity<Page<ManufacturerProductCountDTO>> getManufacturersSortedByProducts(
            @RequestParam
            Integer pageNumber,
            @RequestParam
            @Min(value = 4, message = "pageSize should be at least 4")
            @Max(value = 10, message = "pageSize should be at most 10")
            Integer pageSize,
            @RequestAttribute("user")
            User user
    ) {
        if (!user.getUserRole().getRead_all()) {
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        return new ResponseEntity<>(manufacturerService.getManufacturersSortedByProducts(pageNumber, pageSize), HttpStatus.OK);
    }

    /**
     * Retrieves a specific manufacturer by ID.
     *
     * @param id   the manufacturer ID
     * @param user the user making the request
     * @return a response entity containing the manufacturer if found and the user is authorized, or a not found status if the manufacturer is not found, or an unauthorized status if not authorized
     */
    @GetMapping(path = "/manufacturers/{id}", produces = "application/json")
    public @ResponseBody
    ResponseEntity<ManufacturerDTO> getManufacturer(
            @PathVariable("id")
            Integer id,
            @RequestAttribute("user")
            User user
    ) {
        ManufacturerDTO manufacturerDTO = null;
        try {
            manufacturerDTO = manufacturerService.getManufacturerById(id);
            if (!user.getUserRole().getRead_all() && (!user.getUserRole().getRead_own() || !Objects.equals(manufacturerDTO.getUserHandle(), user.getHandle()))) {
                return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
            }
            return new ResponseEntity<>(manufacturerDTO, HttpStatus.OK);
        } catch (AppException e) {
            return new ResponseEntity<>(null, HttpStatus.NOT_FOUND);
        }
    }

    /**
     * Retrieves a page of products for a specific manufacturer.
     *
     * @param id         the manufacturer ID
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @param user       the user making the request
     * @return a response entity containing a page of products if the manufacturer is found and the user is authorized, or a bad request status if the manufacturer is not found, or an unauthorized status if not authorized
     */
    @GetMapping(path = "/manufacturers/{id}/products", produces = "application/json")
    public @ResponseBody
    ResponseEntity<Page<ProductDTO>> getManufacturerProducts(
            @PathVariable("id")
            Integer id,
            @RequestParam
            Integer pageNumber,
            @RequestParam
            @Min(value = 4, message = "pageSize should be at least 4")
            @Max(value = 10, message = "pageSize should be at most 10")
            Integer pageSize,
            @RequestAttribute("user")
            User user
    ) {
        ManufacturerDTO manufacturerDTO = null;
        try {
            manufacturerDTO = manufacturerService.getManufacturerById(id);
            if (!user.getUserRole().getRead_all() && (!user.getUserRole().getRead_own() || !Objects.equals(manufacturerDTO.getUserHandle(), user.getHandle()))) {
                return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
            }
            return new ResponseEntity<>(productService.getProductsByManufacturerId(id, pageNumber, pageSize), HttpStatus.OK);
        } catch (AppException e) {
            return new ResponseEntity<>(null, HttpStatus.BAD_REQUEST);
        }
    }

    /**
     * Creates a new manufacturer.
     *
     * @param manufacturerDTO the manufacturer to create
     * @param user            the user making the request
     * @return a response entity with a success message if the manufacturer is created and the user is authorized, or an error message if the user is not authorized
     */
    @PostMapping(path = "/manufacturers", produces = "application/json")
    public ResponseEntity<Map<String, String>> createManufacturer(
            @Valid @RequestBody
            ManufacturerDTO manufacturerDTO,
            @RequestAttribute("user")
            User user
    ) {
        Map<String, String> response = new HashMap<>();

        if (!user.getUserRole().getCreate()) {
            response.put("error", "Unauthorized to create resource");
            return new ResponseEntity<>(response, HttpStatus.UNAUTHORIZED);
        }

        try {
            manufacturerDTO.setUserHandle(user.getHandle());
            manufacturerService.createManufacturer(manufacturerDTO);
            response.put("message", "Manufacturer created");
            return new ResponseEntity<>(response, HttpStatus.CREATED);
        } catch (AppException e) {
            response.put("error", e.getMessage());
            return new ResponseEntity<>(response, HttpStatus.BAD_REQUEST);
        }
    }

    /**
     * Updates a manufacturer.
     *
     * @param id              the manufacturer ID
     * @param manufacturerDTO the updated manufacturer details
     * @param user            the user making the request
     * @return a response entity with a success message if the manufacturer is updated and the user is authorized, or an error message if the user is not authorized or the manufacturer is not found
     */
    @PatchMapping(path = "/manufacturers/{id}", produces = "application/json")
    public @ResponseBody
    ResponseEntity<Map<String, String>> updateManufacturer(
            @PathVariable("id")
            Integer id,
            @Valid @RequestBody
            ManufacturerDTO manufacturerDTO,
            @RequestAttribute("user")
            User user
    ) {
        Map<String, String> response = new HashMap<>();
        try {
            ManufacturerDTO oldManufacturerDTO = manufacturerService.getManufacturerById(id);
            if (!user.getUserRole().getUpdate_all() && (!user.getUserRole().getUpdate_own() || !Objects.equals(oldManufacturerDTO.getUserHandle(), user.getHandle()))) {
                response.put("error", "Unauthorized to update resource");
                return new ResponseEntity<>(response, HttpStatus.UNAUTHORIZED);
            }
            if (!user.getUserRole().getUpdate_all() && !Objects.equals(manufacturerDTO.getUserHandle(), user.getHandle())) {
                response.put("error", "Unauthorized to transfer resource between users");
                return new ResponseEntity<>(response, HttpStatus.UNAUTHORIZED);
            }
            manufacturerService.updateManufacturerWithId(id, manufacturerDTO);
            response.put("message", "Manufacturer updated");
            return new ResponseEntity<>(response, HttpStatus.OK);
        } catch (AppException e) {
            response.put("error", e.getMessage());
            return new ResponseEntity<>(response, HttpStatus.BAD_REQUEST);
        }
    }

    /**
     * Deletes a manufacturer.
     *
     * @param id   the manufacturer ID
     * @param user the user making the request
     * @return a response entity with a success message if the manufacturer is deleted and the user is authorized, or an error message if the user is not authorized or the manufacturer is not found
     */
    @DeleteMapping(path = "/manufacturers/{id}", produces = "application/json")
    public @ResponseBody
    ResponseEntity<Map<String, String>> deleteManufacturer(
            @PathVariable("id")
            Integer id,
            @RequestAttribute("user")
            User user
    ) {
        Map<String, String> response = new HashMap<>();
        try {
            ManufacturerDTO manufacturerDTO = manufacturerService.getManufacturerById(id);
            if (!user.getUserRole().getDelete_all() && (!user.getUserRole().getDelete_own() || !Objects.equals(manufacturerDTO.getUserHandle(), user.getHandle()))) {
                response.put("error", "Unauthorized to delete resource");
                return new ResponseEntity<>(response, HttpStatus.UNAUTHORIZED);
            }
            manufacturerService.deleteManufacturerWithId(id);
        } catch (AppException e) {
            throw new RuntimeException(e);
        }
        response.put("message", "Manufacturer deleted");
        return new ResponseEntity<>(response, HttpStatus.OK);
    }

    /**
     * Retrieves a page of manufacturer product counts.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @param user       the user making the request
     * @return a response entity containing a page of manufacturer product counts if the user is authorized, or an unauthorized status if not authorized
     */
    @GetMapping(path = "/manufacturer-product-counts")
    public @ResponseBody
    ResponseEntity<Page<ManufacturerProductCountDTO>> getManufacturerProductCountsPage(
            @RequestParam
            Integer pageNumber,
            @RequestParam
            @Min(value = 4, message = "pageSize should be at least 4")
            @Max(value = 10, message = "pageSize should be at most 10")
            Integer pageSize,
            @RequestAttribute("user")
            User user
    ) {
        if (!user.getUserRole().getRead_all()) {
            return new ResponseEntity<>(null, HttpStatus.UNAUTHORIZED);
        }
        return new ResponseEntity<>(manufacturerService.getManufacturerProductCountsPage(pageNumber, pageSize), HttpStatus.OK);
    }
}
