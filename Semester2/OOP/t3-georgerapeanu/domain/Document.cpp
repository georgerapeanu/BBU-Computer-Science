//
// Created by georgerapeanu on 26.05.2022.
//

#include "Document.h"

Document::Document(const std::string &line) {
    int count_pipes = 0;
    for(auto it:line){
        count_pipes += (it == '|');
    }
    if(count_pipes != 2){
        throw AppException("Invalid line");
    }
    int i = 0;

    while(line[i] != '|'){
        this->name += line[i++];
    }
    i++;
    while(line[i] != '|'){
        this->keywords += line[i++];
    }
    i++;
    while(i < (int)line.size()){
        this->content += line[i++];
    }
    i++;
}

Document::Document() {
    this->name = "";
    this->keywords = "";
    this->content = "";
}

std::string Document::get_name() const {
    return this->name;
}

std::string Document::get_keywords() const {
    return this->keywords;
}

std::string Document::get_content() const {
    return this->content;
}

std::string Document::to_string() const {
    return this->get_name() + ";" + this->get_keywords();
}
