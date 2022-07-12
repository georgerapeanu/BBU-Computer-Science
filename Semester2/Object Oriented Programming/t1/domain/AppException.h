//
// Created by georgerapeanu on 07.04.2022.
//

#ifndef T1_APPEXCEPTION_H
#define T1_APPEXCEPTION_H

#include <string>

class AppException {
    std::string message;

public:

    AppException();

    AppException(std::string message);

    std::string get_message();
};


#endif //T1_APPEXCEPTION_H
