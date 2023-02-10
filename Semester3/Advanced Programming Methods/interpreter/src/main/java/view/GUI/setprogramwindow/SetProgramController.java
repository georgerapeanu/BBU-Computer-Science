package view.GUI.setprogramwindow;

import controller.IController;
import controller.parsers.syntax.SyntaxParser;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import model.exceptions.AppException;
import model.statements.IStatement;
import utils.HardcodedPrograms;
import view.GUI.mainwindow.MainWindowController;

public class SetProgramController {

    MainWindowController siblingController;
    IController controller;

    @FXML
    private TextArea error;

    @FXML
    private Tab hardcodedTab;

    @FXML
    private ListView<IStatement> examplesListView;

    @FXML
    private Button setButton;

    @FXML
    private Tab codeTab;

    @FXML
    private TextArea codeTextArea;

    public SetProgramController(IController controller, MainWindowController siblingController) {
        this.controller = controller;
        this.siblingController = siblingController;
    }

    @FXML
    public void initialize() {
        examplesListView.setItems(FXCollections.observableList(HardcodedPrograms.hardcodedPrograms));
        setButton.setOnAction(actionEvent -> {
            try {
                if (codeTab.isSelected()) {
                    String code = codeTextArea.getText();
                    controller.setProgram(SyntaxParser.parse(code));
                    this.error.setText("Ok!");
                    this.error.setStyle("-fx-text-fill: green");
                } else if (hardcodedTab.isSelected()) {
                    int index = examplesListView.getSelectionModel().getSelectedIndex();
                    if (index < 0) {
                        throw new AppException("No index selected");
                    } else if (index >= HardcodedPrograms.hardcodedPrograms.size()) {
                        throw new AppException("No program at selected index");
                    }
                    this.controller.setProgram(HardcodedPrograms.hardcodedPrograms.get(index));
                } else {
                    throw new AppException("No tab selected");
                }
            }catch (AppException e) {
                this.error.setText("Error: " + e.toString());
                this.error.setStyle("-fx-text-fill: red");
            } finally {
                this.siblingController.refresh();
            };
        });
    }
}
