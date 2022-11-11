import controller.Controller;
import controller.IController;
import model.exceptions.AppException;
import repository.IRepository;
import repository.Repository;
import view.IMainView;
import view.MainView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException, AppException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Select logfilePath:");
        String line = reader.readLine().trim();
        if(line.equals("")){
            line = null;
        }
        IRepository repository = new Repository(line);
        IController controller = new Controller(repository, false);
        IMainView view = new MainView(controller);
        view.run();
    }
}