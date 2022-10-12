package Repository;

import Model.IVehicle;

import java.util.ArrayList;
import java.util.List;

public class VehicleRepository implements IVehicleRepository {

    private IVehicle []vehicles;
    private int size;
    static private final int capacity = 100;

    public VehicleRepository(){
        this.vehicles = new IVehicle[capacity];
        this.size = 0;
    }

    @Override
    public void add(IVehicle vehicle) throws RepositoryException {
        if(this.size == capacity){
            throw new RepositoryException("Repository at maximum capacity");
        }
        for(int i = 0; i < this.size; i++) {
            if(vehicles[i].getId() == vehicle.getId()){
                throw new RepositoryException("Duplicate id in repository");
            }
        }
        this.vehicles[this.size++] = vehicle;
    }

    @Override
    public void remove(IVehicle vehicle) throws RepositoryException {
        for(int i = 0;i < this.size;i++){
            if(this.vehicles[i].getId() == vehicle.getId()){
                for(int j = i;j + 1 < this.size;j++){
                    this.vehicles[j] = this.vehicles[j + 1];
                }
                this.size--;
                return ;
            }
        }
        throw new RepositoryException("No such vehicle exists");
    }

    @Override
    public List<IVehicle> getAll(){
        List<IVehicle> vehicles = new ArrayList<IVehicle>();
        for(int i = 0;i < this.size;i++){
            vehicles.add(this.vehicles[i]);
        }
        return vehicles;
    }
}
