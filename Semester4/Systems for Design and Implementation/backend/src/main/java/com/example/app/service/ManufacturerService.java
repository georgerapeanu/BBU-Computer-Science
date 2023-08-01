package com.example.app.service;

import com.example.app.dto.ManufacturerProductCountDTO;
import com.example.app.exceptions.AppException;
import com.example.app.model.Manufacturer;
import com.example.app.dto.model.ManufacturerDTO;
import com.example.app.model.User;
import com.example.app.repository.ManufacturerRepository;
import com.example.app.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageImpl;
import org.springframework.data.domain.PageRequest;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.stream.Collectors;

/**
 * The manufacturer service implementation.
 */
@Service
public class ManufacturerService implements IManufacturerService {

    @Autowired
    ManufacturerRepository manufacturerRepository;

    @Autowired
    UserRepository userRepository;

    /**
     * Retrieves all manufacturers with pagination.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing the list of ManufacturerDTOs
     */
    public Page<ManufacturerDTO> getAllManufacturers(Integer pageNumber, Integer pageSize) {
        return manufacturerRepository.findAll(PageRequest.of(pageNumber, pageSize))
                .map(ManufacturerDTO::fromManufacturer);
    }

    /**
     * Retrieves a manufacturer by its ID.
     *
     * @param id the manufacturer ID
     * @return the ManufacturerDTO object
     * @throws AppException if no manufacturer with the specified ID is found
     */
    public ManufacturerDTO getManufacturerById(Integer id) throws AppException {
        Manufacturer manufacturer = manufacturerRepository.findById(id).orElse(null);
        if (manufacturer == null) {
            throw new AppException("No manufacturer with such id exists");
        }
        return ManufacturerDTO.fromManufacturer(manufacturer);
    }

    /**
     * Creates a new manufacturer.
     *
     * @param manufacturerDTO the ManufacturerDTO object containing the manufacturer details
     * @throws AppException if the user handle is invalid
     */
    public void createManufacturer(ManufacturerDTO manufacturerDTO) throws AppException {
        User user = userRepository.findById(manufacturerDTO.getUserHandle()).orElse(null);
        if (user == null) {
            throw new AppException("Invalid user handle specified");
        }
        manufacturerRepository.save(ManufacturerDTO.toManufacturer(manufacturerDTO, user));
    }

    /**
     * Updates a manufacturer with the specified ID.
     *
     * @param id              the manufacturer ID
     * @param manufacturerDTO the ManufacturerDTO object containing the updated manufacturer details
     * @throws AppException if no manufacturer with the specified ID is found or the user handle is invalid
     */
    public void updateManufacturerWithId(Integer id, ManufacturerDTO manufacturerDTO) throws AppException {
        Manufacturer repoManufacturer = manufacturerRepository.findById(id).orElse(null);
        if (repoManufacturer == null) {
            throw new AppException("No such manufacturer found in repository");
        }
        User user = userRepository.findById(manufacturerDTO.getUserHandle()).orElse(null);
        if (user == null) {
            throw new AppException("Invalid user handle specified");
        }
        Manufacturer manufacturer = ManufacturerDTO.toManufacturer(manufacturerDTO, user);
        manufacturer.setId(repoManufacturer.getId());
        manufacturerRepository.save(manufacturer);
    }

    /**
     * Deletes a manufacturer with the specified ID.
     *
     * @param id the manufacturer ID
     */
    public void deleteManufacturerWithId(Integer id) {
        manufacturerRepository.deleteById(id);
    }

    /**
     * Retrieves manufacturers sorted by the number of products they have.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing the list of ManufacturerProductCountDTOs
     */
    @Override
    public Page<ManufacturerProductCountDTO> getManufacturersSortedByProducts(Integer pageNumber, Integer pageSize) {
        return manufacturerRepository
                .getManufacturersSortedByProductCount(PageRequest.of(pageNumber, pageSize));
    }

    /**
     * Retrieves a page of ManufacturerProductCountDTOs representing the number of products for each manufacturer.
     *
     * @param pageNumber the page number
     * @param pageSize   the page size
     * @return a Page object containing the list of ManufacturerProductCountDTOs
     */
    @Override
    public Page<ManufacturerProductCountDTO> getManufacturerProductCountsPage(Integer pageNumber, Integer pageSize) {
        Page<ManufacturerDTO> manufacturerDTOPage = manufacturerRepository
                .findAll(PageRequest.of(pageNumber, pageSize))
                .map(ManufacturerDTO::fromManufacturer);

        return new PageImpl<>(
                manufacturerRepository.getManufacturerProductCountsFromList(manufacturerDTOPage.getContent()),
                PageRequest.of(pageNumber, pageSize),
                manufacturerDTOPage.getTotalElements()
        );
    }
}
