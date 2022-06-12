//
// Created by georgerapeanu on 11.06.2022.
//

#include <string>
#include "AppException.h"

AppException::AppException(const std::__cxx11::basic_string<char> &arg) : runtime_error(arg) {}
