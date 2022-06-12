//
// Created by georgerapeanu on 11.06.2022.
//

#ifndef PRACTICAL_APPEXCEPTION_H
#define PRACTICAL_APPEXCEPTION_H

#include <stdexcept>
#include <string>

class AppException : public std::runtime_error {
public:
    AppException(const std::string &arg);
};

#endif //PRACTICAL_APPEXCEPTION_H
