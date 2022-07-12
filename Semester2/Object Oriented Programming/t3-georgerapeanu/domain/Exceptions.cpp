//
// Created by georgerapeanu on 26.05.2022.
//

#include "Exceptions.h"

AppException::AppException(std::string message) {
    this->message = message;
}

std::string AppException::get_message() {
    return this->message;
}
