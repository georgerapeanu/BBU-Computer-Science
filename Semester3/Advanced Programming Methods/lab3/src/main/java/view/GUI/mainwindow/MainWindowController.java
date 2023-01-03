package view.GUI.mainwindow;

import controller.IController;
import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Callback;
import javafx.util.Pair;
import model.exceptions.AppException;
import model.state.IFileTable;
import model.state.IHeap;
import model.state.IOutput;
import model.state.ProgState;
import model.statements.IStatement;
import model.values.IValue;

import java.util.Collections;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.stream.Collectors;

public class MainWindowController {
    IController controller;
    IHeap currentHeap;
    IOutput currentOut;
    IFileTable currentFileTable;

    public MainWindowController(IController controller) {
        this.controller = controller;
    }

    @FXML
    private Label progStatesLabel;
    @FXML
    private ListView<Integer> progStatesListView;
    @FXML
    private TableView<Pair<Integer, IValue>> heapTableTableView;
    @FXML
    private TableColumn<Pair<Integer, IValue>, Integer> heapAddressColumn;
    @FXML
    private TableColumn<Pair<Integer, IValue>, String> heapValueColumn;
    @FXML
    private ListView<String> outListView;
    @FXML
    private ListView<String> fileTableListView;
    @FXML
    private TableView<Pair<String, IValue>> symTableTableView;
    @FXML
    private TableColumn<Pair<String, IValue>, String> symbolNameColumn;
    @FXML
    private TableColumn<Pair<String, IValue>, String> symbolValueColumn;
    @FXML
    private ListView<IStatement> executionStackListView;

    @FXML
    private Button stepButton;
    @FXML
    private Button runButton;
    //TODO after run or last step the programs are removed so nothing is displayed anymore
    public void refresh(){
        Integer id = this.progStatesListView.getSelectionModel().getSelectedItem();
        this.progStatesListView.getItems().clear();
        this.heapTableTableView.getItems().clear();
        this.outListView.getItems().clear();
        this.fileTableListView.getItems().clear();
        this.symTableTableView.getItems().clear();
        this.executionStackListView.getItems().clear();

        this.progStatesLabel.setText("Program states: " + Integer.toString(this.controller.getProgStates().size()));
        this.controller.getProgStates().forEach(x -> this.progStatesListView.getItems().add(x.getId()));
        if(this.controller.getProgStates().size() > 0){
            this.currentHeap = this.controller.getProgStates().get(0).getHeap();
            this.currentOut = this.controller.getProgStates().get(0).getOutput();
            this.currentFileTable = this.controller.getProgStates().get(0).getFileTable();
        }
        if(this.currentHeap != null) {
            this.currentHeap.toMap().forEach((x, y) -> this.heapTableTableView.getItems().add(new Pair<>(x, y)));
        }
        if(this.currentOut != null) {
            this.currentOut.getOutputAsList().forEach(x -> {
                this.outListView.getItems().add(x);
            });
        }
        if(this.currentFileTable != null) {
            this.currentFileTable.getFileList().forEach(x -> {
                this.fileTableListView.getItems().add(x);
            });
        }
        ProgState currentProgram;
        try {
            currentProgram = this.controller.getProgStates().stream().filter(x -> Integer.valueOf(x.getId()).equals(id)).findAny().get();
            currentProgram.getSymTable().toMap().forEach((x, y) -> this.symTableTableView.getItems().add(new Pair<>(x,y)));
            List<IStatement> statementList = currentProgram.getExecutionStack().toList();
            for(int i = statementList.size() - 1;i >= 0;i--){
                this.executionStackListView.getItems().add(statementList.get(i));
            }

            this.progStatesListView.getSelectionModel().select(id);
        } catch (NoSuchElementException e) {
            return ;
        } finally {
            this.progStatesListView.refresh();
            this.heapTableTableView.refresh();
            this.outListView.refresh();
            this.fileTableListView.refresh();
            this.symTableTableView.refresh();
            this.executionStackListView.refresh();
        }
    }

    @FXML
    public void initialize() {
        this.heapAddressColumn.setCellValueFactory(p -> new SimpleIntegerProperty(p.getValue().getKey()).asObject());
        this.heapValueColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue().toString()));
        this.symbolNameColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getKey()));
        this.symbolValueColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue().toString()));
        this.refresh();
        this.runButton.setOnAction(actionEvent -> {
            try {
                this.controller.executeAllSteps();
            } catch (AppException e) {
                Alert alert = new Alert(Alert.AlertType.ERROR, e.toString(), ButtonType.OK);
                alert.showAndWait();
            } finally {
                this.refresh();
            }
        });
        this.stepButton.setOnAction(actionEvent ->{
            try {
                this.controller.executeOneStep();
            } catch (AppException e) {
                Alert alert = new Alert(Alert.AlertType.ERROR, e.toString(), ButtonType.OK);
                alert.showAndWait();
            } finally {
                this.refresh();
            }
        });
        this.progStatesListView.setOnMouseClicked(x -> this.refresh());
    }

}
