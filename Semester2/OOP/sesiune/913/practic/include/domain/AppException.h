//
// Created by georgerapeanu on 09.06.2022.
//

#ifndef PRACTIC_APPEXCEPTION_H
#define PRACTIC_APPEXCEPTION_H

#include <stdexcept>

class AppException : public std::runtime_error{
public:
    AppException(const std::string& msg);
};

#endif //PRACTIC_APPEXCEPTION_H
