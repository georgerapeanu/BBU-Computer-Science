package Model;

public class Motorcycle implements IVehicle {
    private final String color;
    private final int id;

    public Motorcycle(int id, String color){
        this.id = id;
        this.color = color;
    }


    @Override
    public int getId(){
        return this.id;
    }

    @Override
    public String getDescription() {
        return "Motorcycle #" + String.valueOf(this.id) + " of color " + this.color;
    }


    @Override
    public String getColor(){
        return this.color;
    }
}