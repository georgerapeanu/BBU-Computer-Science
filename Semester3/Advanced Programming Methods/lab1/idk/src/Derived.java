public class Derived implements Base {
    public String getMessage(){
        return "derived";
    }
    public static void tmp() throws TmpException {
        throw new TmpException();
    }
}
