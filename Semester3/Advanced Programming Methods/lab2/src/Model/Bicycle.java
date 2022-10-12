package Model;

public class Bicycle implements IVehicle {
    private final String color;
    private final int id;

    public Bicycle(int id, String color){
        this.id = id;
        this.color = color;
    }

    @Override
    public int getId(){
        return this.id;
    }

    @Override
    public String getDescription() {
        return "Bicycle #" + String.valueOf(this.id) + " of color " + this.color;
    }

    @Override
    public String getColor(){
        return this.color;
    }
}