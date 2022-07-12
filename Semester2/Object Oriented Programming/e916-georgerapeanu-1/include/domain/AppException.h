//
// Created by georgerapeanu on 12.06.2022.
//

#ifndef E916_GEORGERAPEANU_1_APPEXCEPTION_H
#define E916_GEORGERAPEANU_1_APPEXCEPTION_H
#include <stdexcept>

class AppException : public std::runtime_error{
public:
    AppException(const std::string &arg);
};


#endif //E916_GEORGERAPEANU_1_APPEXCEPTION_H
