import controller.Controller;
import controller.IController;
import repository.IRepository;
import repository.Repository;
import view.IView;
import view.View;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Select logfilePath:");
        String line = reader.readLine().trim();
        if(line.equals("")){
            line = null;
        }
        IRepository repository = new Repository(line);
        IController controller = new Controller(repository, false);
        IView view = new View(controller);
        view.run();
    }
}