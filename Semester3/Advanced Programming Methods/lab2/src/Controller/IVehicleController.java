package Controller;

import Model.IVehicle;
import Repository.RepositoryException;

import java.util.List;

public interface IVehicleController {
    void addCar(int id, String color) throws RepositoryException;
    void addBicycle(int id, String color) throws RepositoryException;
    void addMotorcycle(int id, String color) throws RepositoryException;
    void removeVehicle(int id) throws RepositoryException;
    List<IVehicle> getVehiclesWithColor(String color);
}
