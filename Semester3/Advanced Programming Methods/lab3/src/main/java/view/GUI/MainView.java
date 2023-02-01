package view.GUI;

import controller.IController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import model.exceptions.AppException;
import view.GUI.mainwindow.MainWindowController;
import view.GUI.setprogramwindow.SetProgramController;
import view.IMainView;

public class MainView extends Application implements IMainView {
    private static IController controller;

    public static void setController(IController controller) {
        MainView.controller = controller;
    }

    @Override
    public void start(Stage primaryStage) {
        try {
            FXMLLoader mainWindowLoader = new FXMLLoader();
            mainWindowLoader.setLocation(getClass().getResource("mainwindow/MainWindow.fxml"));
            mainWindowLoader.setControllerFactory(c -> new MainWindowController(MainView.controller));
            Parent mainWindowRoot = mainWindowLoader.load();
            MainWindowController mainWindowController = mainWindowLoader.getController();
            primaryStage.setTitle("Interpreter");
            primaryStage.setScene(new Scene(mainWindowRoot));
            primaryStage.show();

            Stage secondaryStage = new Stage();
            FXMLLoader setProgramLoader = new FXMLLoader();
            setProgramLoader.setControllerFactory(c -> new SetProgramController(MainView.controller, mainWindowController));
            setProgramLoader.setLocation(getClass().getResource("setprogramwindow/SetProgramWindow.fxml"));
            Parent setProgramRoot = setProgramLoader.load();
            SetProgramController setProgramController = setProgramLoader.getController();
            secondaryStage.setTitle("Select program");
            secondaryStage.setScene(new Scene(setProgramRoot));
            secondaryStage.show();
        } catch (Exception exception) {
            throw new RuntimeException(exception);
        }
    }

    @Override
    public void run(String[] args) throws AppException {
        launch(args);
    }

    public void main(String[] args) throws AppException{
        launch(args);
    }
}
