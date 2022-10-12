package View;

import Controller.IVehicleController;
import Model.IVehicle;
import Repository.RepositoryException;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;
import java.util.Objects;

public class View {
    IVehicleController controller;

    public View(IVehicleController controller) {
        this.controller = controller;
    }

    void handleAdd(String[] args) throws ViewException {
        if(args.length != 4) {
            throw new ViewException("Invalid arguments for add!");
        }

        int id = 0;
        try{
            id = Integer.parseInt(args[1]);
        } catch (NumberFormatException exception) {
            throw new ViewException("Invalid id");
        }

        try{
            switch (args[2]) {
                case "bicycle" -> this.controller.addBicycle(id, args[3]);
                case "motorcycle" -> this.controller.addMotorcycle(id, args[3]);
                case "car" -> this.controller.addCar(id, args[3]);
                default -> throw new ViewException("Invalid vehicle for add!");
            }
        } catch(RepositoryException exception){
            throw new ViewException(exception.getMessage());
        }
    }

    void handleRemove(String[] args) throws ViewException {
        if(args.length != 2) {
            throw new ViewException("Invalid arguments for remove!");
        }
        try{
            this.controller.removeVehicle(Integer.parseInt(args[1]));
        }catch(NumberFormatException exception){
            throw new ViewException("Invalid id for remove!");
        }catch(RepositoryException exception){
            throw new ViewException(exception.getMessage());
        }
    }


    private void handleGet(String[] args) throws ViewException {
        if(args.length != 2){
            throw new ViewException("Invalid arguments for get!");
        }
        List< IVehicle> vehicles = this.controller.getVehiclesWithColor(args[1]);

        for(IVehicle vehicle: vehicles) {
            System.out.println(vehicle.getDescription());
        }
    }

    public void handleHelp() {
        System.out.println("Usage:");
        System.out.println("add ID VEHICLE_TYPE COLOR");
        System.out.println("remove ID");
        System.out.println("get COLOR");
        System.out.println("help");
        System.out.println("exit");
    }

    public void run(){
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        while(true){
            try{
                System.out.print("Enter command>");
                String cmd = reader.readLine().strip().toLowerCase();
                String[] args = cmd.split(" ");
                if(args.length > 0){
                    if(Objects.equals(args[0], "add")){
                        this.handleAdd(args);
                    } else if(Objects.equals(args[0], "remove")){
                        this.handleRemove(args);
                    } else if(Objects.equals(args[0], "get")){
                        this.handleGet(args);
                    }else if(Objects.equals(args[0], "help")){
                        this.handleHelp();
                    }else if(Objects.equals(args[0], "exit")){
                        break;
                    }else{
                        throw new ViewException("Invalid command!");
                    }
                } else {
                    throw new ViewException("Invalid command!");
                }
            } catch (IOException exception) {
                break;
            } catch (ViewException exception){
                System.out.println(exception.getMessage());
            }
        }
    }

}
