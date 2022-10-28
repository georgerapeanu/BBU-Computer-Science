package model.state;

import model.abstract_data_types.generic_list.GenericList;

import java.util.List;

public class Output implements  IOutput{
    GenericList<String> data;

    public Output() {
        this.data = new GenericList<>();
    }

    @Override
    public List<String> getOutputAsList(String string) {
        return this.data.getAll();
    }

    @Override
    public String getOutput(String string) {
        StringBuilder answer = new StringBuilder();
        for(String elem:this.data.getAll()){
            answer.append(elem);
        }
        return answer.toString();
    }

    @Override
    public void appendToOutput(String string) {
        this.data.addToEnd(string);
    }

    @Override
    public void setOutput(String string) {
        this.data.clear();
        this.data.addToEnd(string);
    }
}
