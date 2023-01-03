import controller.Controller;
import controller.IController;
import model.exceptions.AppException;
import repository.IRepository;
import repository.Repository;
import view.CLI.MainView;
import view.IMainView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.concurrent.Executors;

public class Main {
    public static void main(String[] args) throws IOException, AppException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Select logfilePath:");
        String line = reader.readLine().trim();
        if(line.equals("")){
            line = null;
        }
        IRepository repository = new Repository(line);
        IController controller = new Controller(repository, Executors.newFixedThreadPool(2),false);
        view.GUI.MainView.setController(controller);
        IMainView view = new view.GUI.MainView();
        view.run(args);
    }
}