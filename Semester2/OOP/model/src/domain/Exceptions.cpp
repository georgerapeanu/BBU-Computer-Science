//
// Created by georgerapeanu on 08.06.2022.
//

#include "Exceptions.h"

AppException::AppException(const std::string &message) : runtime_error(message) {
    ;
}
