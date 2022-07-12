/*!
 * @file this file contains the implementation for the Exceptions
 */
//
// Created by georgerapeanu on 28.03.2022.
//

#include "Exceptions.h"

AppException::AppException(const std::string &message){
    this->message = message;
}
std::string AppException::get_message()const{
    return this->message;
}

DomainException::DomainException(const std::string &message) : AppException(message) {
    ;
}

DynamicVectorException::DynamicVectorException(const std::string &message) : DomainException(message) {
    ;
}

RepositoryException::RepositoryException(const std::string &message) : AppException(message) {
    ;
}

ControllerException::ControllerException(const std::string &message) : AppException(message) {
    ;
}

MovieControllerException::MovieControllerException(const std::string &message) : ControllerException(message) {
    ;
}

UIException::UIException(const std::string &message) : AppException(message) {
    ;
}
