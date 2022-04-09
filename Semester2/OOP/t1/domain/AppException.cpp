//
// Created by georgerapeanu on 07.04.2022.
//

#include "AppException.h"

AppException::AppException() {
    this->message = "";
}

AppException::AppException(std::string message) {
    this->message = message;
}

std::string AppException::get_message() {
    return this->message;
}
