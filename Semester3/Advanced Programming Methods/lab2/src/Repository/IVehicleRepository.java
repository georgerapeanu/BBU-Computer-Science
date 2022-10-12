package Repository;

import Model.IVehicle;

import java.util.List;

public interface IVehicleRepository {
    void add(IVehicle vehicle) throws RepositoryException;
    void remove(IVehicle vehicle) throws RepositoryException;
    List<IVehicle> getAll();
}
