//
// Created by georgerapeanu on 26.05.2022.
//

#include "FileRepository.h"
#include <fstream>
#include "Exceptions.h"

FileRepository::FileRepository(std::string filename) {
    std::ifstream f(filename);
    if(!f){
        throw AppException("File doesn't exist");
    }

    std::string line;

    while(std::getline(f, line, '\n')){
        this->entities.push_back(Document(line));
    }
    f.close();
}

std::vector<Document> FileRepository::get_all() {
    return this->entities;
}
