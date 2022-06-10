//
// Created by georgerapeanu on 26.05.2022.
//

#ifndef T3_GEORGERAPEANU_FILEREPOSITORY_H
#define T3_GEORGERAPEANU_FILEREPOSITORY_H

#include <string>
#include <vector>
#include "Document.h"
#include <fstream>

class FileRepository {
    std::vector<Document> entities;

public:

    FileRepository(std::string filename);
    std::vector<Document> get_all();
};


#endif //T3_GEORGERAPEANU_FILEREPOSITORY_H
