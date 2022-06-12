//
// Created by georgerapeanu on 12.06.2022.
//

#include "AppException.h"

AppException::AppException(const std::string &arg) : runtime_error(arg) {}
