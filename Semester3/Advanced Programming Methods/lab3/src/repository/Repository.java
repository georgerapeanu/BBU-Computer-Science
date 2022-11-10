package repository;

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
    public ProgState getCurrentProgram() {
        return programs.get(0);
    }

    @Override
    public void addProgram(ProgState program) {
        programs.add(program);
    }

    @Override
    public void logProgramState() throws IOException {
        if(this.logFilePath != null) {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
            logFile.println(this.programs.get(0).toString());
            logFile.close();
        }
    }

    @Override
    public void clear() {
        programs = new ArrayList<>();
    }
}
