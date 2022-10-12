import Controller.IVehicleController;
import Controller.VehicleController;
import Repository.IVehicleRepository;
import Repository.VehicleRepository;
import View.View;

public class Main {
    public static void main(String[] args) {
        IVehicleRepository repository = new VehicleRepository();
        IVehicleController controller = new VehicleController(repository);
        View view = new View(controller);
        view.run();
    }
}