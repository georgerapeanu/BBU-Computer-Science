public class Main {
    public static void main(String[] args) {
        int sum = 0;
        for(String arg: args){
            int number = Integer.parseInt(arg);
            sum += number;
        }
        System.out.println(args.length == 0 ? "Cannot average 0 numbers": (double) sum / args.length);
    }
}