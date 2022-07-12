//
// Created by georgerapeanu on 26.05.2022.
//

#ifndef T3_GEORGERAPEANU_DOCUMENT_H
#define T3_GEORGERAPEANU_DOCUMENT_H

#include <string>
#include <vector>
#include "Exceptions.h"

class Document {
private:
    std::string name;
    std::string keywords;
    std::string content;

public:

    Document();

    Document(const std::string &line);

    std::string get_name()const;
    std::string get_keywords()const;
    std::string get_content()const;
    std::string to_string()const;
};


#endif //T3_GEORGERAPEANU_DOCUMENT_H
