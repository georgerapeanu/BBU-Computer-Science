//
// Created by georgerapeanu on 26.05.2022.
//

#ifndef T3_GEORGERAPEANU_EXCEPTIONS_H
#define T3_GEORGERAPEANU_EXCEPTIONS_H

#include <string>

class AppException{
    std::string message;

public:

    AppException(std::string message);

    std::string get_message();
};


#endif //T3_GEORGERAPEANU_EXCEPTIONS_H
