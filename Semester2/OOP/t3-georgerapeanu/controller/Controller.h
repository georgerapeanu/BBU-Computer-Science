//
// Created by georgerapeanu on 26.05.2022.
//

#ifndef T3_GEORGERAPEANU_CONTROLLER_H
#define T3_GEORGERAPEANU_CONTROLLER_H

#include "FileRepository.h"

class Controller {
    FileRepository& repository;
public:
    Controller(FileRepository& repository);
    std::vector<Document> get_all_documents_sorted_by_description_length_containing(std::string& s);
    double get_similarity(const Document &a, std::string s);
};


#endif //T3_GEORGERAPEANU_CONTROLLER_H
