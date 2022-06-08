//
// Created by georgerapeanu on 08.06.2022.
//

#include "UserController.h"

UserController::UserController(GeneralFileRepository<User> &users) : users(users) {

}

std::vector<User> UserController::getAll() {
    return this->users.getAll();
}