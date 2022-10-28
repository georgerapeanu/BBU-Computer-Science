package model.state;

import java.util.List;

public interface IOutput {
    public List<String> getOutputAsList();
    public String getOutput();
    public void appendToOutput(String string);
    public void setOutput(String string);
    public String toDebug();
}
