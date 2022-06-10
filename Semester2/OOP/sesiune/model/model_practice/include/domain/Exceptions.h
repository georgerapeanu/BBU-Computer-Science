//
// Created by georgerapeanu on 08.06.2022.
//

#ifndef MODEL_EXCEPTIONS_H
#define MODEL_EXCEPTIONS_H

#include <exception>
#include <string>
#include <stdexcept>

class AppException: public std::runtime_error{
public:
    AppException(const std::string &message);
};

#endif //MODEL_EXCEPTIONS_H
