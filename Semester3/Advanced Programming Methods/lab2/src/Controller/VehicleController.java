package Controller;

import Model.*;
import Repository.IVehicleRepository;
import Repository.RepositoryException;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class VehicleController implements IVehicleController {
    IVehicleRepository repository;

    public VehicleController(IVehicleRepository repository) {
        this.repository = repository;
    }

    @Override
    public void addCar(int id, String color) throws RepositoryException {
        this.repository.add(new Car(id, color));
    }

    @Override
    public void addBicycle(int id, String color) throws RepositoryException {
        this.repository.add(new Bicycle(id, color));
    }

    @Override
    public void addMotorcycle(int id, String color) throws RepositoryException {
        this.repository.add(new Motorcycle(id, color));
    }

    @Override
    public void removeVehicle(int id) throws RepositoryException {
        this.repository.remove(new DTOVehicle(id, ""));
    }

    @Override
    public List<IVehicle> getVehiclesWithColor(String color) {
        List<IVehicle> vehicles = new ArrayList<IVehicle>();
        for(IVehicle vehicle: this.repository.getAll()){
            if(Objects.equals(vehicle.getColor(), color)){
                vehicles.add(vehicle);
            }
        }
        return vehicles;
    }
}
