//
// Created by georgerapeanu on 09.06.2022.
//

#include "AppException.h"

AppException::AppException(const std::string &msg) : std::runtime_error(msg) {
    ;
}
