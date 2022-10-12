public class Main {
    public static void main(String[] args) throws TmpException {
        Base b1 = new Derived();
        Base b2 = new Derived2();
        System.out.println(b1.getMessage());
        System.out.println(b2.getMessage());
        Derived.tmp();
    }
}