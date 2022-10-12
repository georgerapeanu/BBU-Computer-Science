package Model;

public record DTOVehicle(int id, String color) implements IVehicle {

    @Override
    public int getId(){
        return id;
    }

    @Override
    public String getDescription() {
        return "";
    }


    @Override
    public String getColor(){
        return color;
    }
}
