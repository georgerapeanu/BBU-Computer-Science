//
// Created by georgerapeanu on 08.06.2022.
//

#ifndef MODEL_USERCONTROLLER_H
#define MODEL_USERCONTROLLER_H

#include "GeneralFileRepository.h"
#include "User.h"

class UserController{
    GeneralFileRepository<User> &users;
public:

    UserController(GeneralFileRepository<User> &users);
    std::vector<User> getAll();
};

#endif //MODEL_USERCONTROLLER_H
