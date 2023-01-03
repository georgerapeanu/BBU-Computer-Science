package repository;

import model.exceptions.AppException;
import model.state.ProgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository{
    String logFilePath;
    List<ProgState> programs;
    public Repository(String logFilePath) {
        programs = new ArrayList<>();
        this.logFilePath = logFilePath;
    }

    @Override
    public List<ProgState> getProgramsList() {
        return programs;
    }

    @Override
    public void setProgramsList(List<ProgState> programs) {
        this.programs = programs;
    }

    @Override
    public void addProgram(ProgState program) {
        programs.add(program);
    }

    @Override
    public void logProgramState(ProgState program) {
        if(this.logFilePath != null) {
            PrintWriter logFile = null;
            try {
                logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            logFile.println(program.toString());
            logFile.close();
        }
    }

    @Override
    public void clear() {
        programs = new ArrayList<>();
    }
}
