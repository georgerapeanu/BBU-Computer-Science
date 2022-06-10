/*!
 * @file Exceptions.h this file contains the models for all exceptions used in app.
 */
//
// Created by georgerapeanu on 20.03.2022.
//

#ifndef A5_6_GEORGERAPEANU_EXCEPTIONS_H
#define A5_6_GEORGERAPEANU_EXCEPTIONS_H
#pragma once
#include <string>
/*!
 * The base app exception.
 */
class AppException:public std::exception{
    //! the message to be displayed
    std::string message;
    public:
    AppException(const std::string &message);
    std::string get_message()const;
};

/*!
 * Domain Exception
 */
class DomainException:public AppException{
    public:
    DomainException(const std::string &message);
};

/*!
 * Repository Exception
 */
class RepositoryException:public AppException{
public:
    RepositoryException(const std::string &message);
};

/*!
 * Controller Exception
 */
class ControllerException:public AppException{
public:
    ControllerException(const std::string &message);
};

/*!
 * Controller Exception
 */
class MovieControllerException:public ControllerException{
public:
    MovieControllerException(const std::string &message);
};

/*!
 * UI Exception
 */
class UIException:public AppException{
public:
    UIException(const std::string &message);
};

/*!
 * Undo Exception
 */
class UndoException:public AppException{
public:
    UndoException(const std::string &message);
};

#endif //A5_6_GEORGERAPEANU_EXCEPTIONS_H
