//
// Created by georgerapeanu on 08.06.2022.
//

#ifndef MODEL_USER_H
#define MODEL_USER_H

#include <string>

class User{
    std::string name;
    std::string type;
public:
    User();

    User(const std::string &name, const std::string &type);

    const std::string getId() const;

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getType() const;

    void setType(const std::string &type);

    friend std::istream& operator >> (std::istream& stream, User &user);

    friend std::ostream& operator << (std::ostream& stream, const User &user);

    bool operator == (const User &other)const;
};

#endif //MODEL_USER_H
