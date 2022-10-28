package model.state;

import java.util.List;

public interface IOutput {
    public List<String> getOutputAsList(String string);
    public String getOutput(String string);
    public void appendToOutput(String string);
    public void setOutput(String string);
}
