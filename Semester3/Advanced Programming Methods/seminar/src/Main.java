import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {
        List<Integer> numbers = Arrays.asList(1, 2, 3 ,4 ,5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
        //a) keep only the numbers which are multiple of 5 or multiple of 2
        List<Integer> firstList = numbers.stream()
                                .filter(x -> x % 2 == 0 || x % 5 == 0)
                                .collect(Collectors.toList());
        System.out.println(firstList);
        //b) transform each remaining number into a string that consists of a prefix "N" and the suffix "R"
        List<String> secondList = firstList.stream()
                                .map(x -> "N" + x.toString() + "R")
                                .collect(Collectors.toList());
        System.out.println(secondList);
        //c) concatenate all the Strings
        String last = secondList.stream()
                .reduce("", (x, y) -> x + y);
        System.out.println(last);
    }
}