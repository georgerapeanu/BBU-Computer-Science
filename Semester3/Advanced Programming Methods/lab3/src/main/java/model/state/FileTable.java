package model.state;

import model.abstract_data_types.generic_dictionary.GenericDictionary;
import model.abstract_data_types.generic_dictionary.IGenericDictionary;
import model.abstract_data_types.generic_dictionary.exceptions.KeyNotFoundAppException;
import model.exceptions.AppException;
import model.state.exceptions.FileAlreadyOpenAppException;
import model.state.exceptions.FileNotOpenAppException;
import model.state.exceptions.InvalidFileFormatAppException;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;

public class FileTable implements IFileTable{
    IGenericDictionary<String, BufferedReader> files;

    public FileTable() {
        this.files = new GenericDictionary<>();
    }

    @Override
    public void openFile(String name) throws AppException {
        if(files.exists(name)){
            throw new FileAlreadyOpenAppException("File " + name + " already open for reading");
        }
        try {
            BufferedReader reader = new BufferedReader(new FileReader(name));
            this.files.setValue(name, reader);
        } catch (FileNotFoundException e) {
            throw new AppException("Error opening file " + name);
        }
    }

    @Override
    public void closeFile(String name) throws AppException {
        try{
            files.removeKey(name);
        }catch(KeyNotFoundAppException exception){
            throw new FileNotOpenAppException("File " + name + " cannot be closed");
        }
    }

    @Override
    public int readFile(String name) throws AppException{
        BufferedReader reader = null;
        try{
            reader = files.getValue(name);
        }catch(KeyNotFoundAppException exception){
            throw new FileNotOpenAppException("File " + name + " cannot be read from");
        }
        String data;
        try {
            data = reader.readLine();
        } catch (IOException e) {
            throw new InvalidFileFormatAppException("Invalid line in file");
        }

        if(data == null){
            data = "0";
        }

        int answer = 0;
        try {
            answer = Integer.parseInt(data);
        } catch (NumberFormatException exception) {
            throw new InvalidFileFormatAppException("Invalid line in file");
        }
        return answer;
    }

    @Override
    public String toString(){
        StringBuilder answer = new StringBuilder();
        answer.append("Filetable:\n");
        for(String name: files.getKeys()){
            answer.append(name).append("\n");
        }
        return answer.toString();
    }

    @Override
    public List<String> getFileList() {
        return this.files.getKeys();
    }
}
