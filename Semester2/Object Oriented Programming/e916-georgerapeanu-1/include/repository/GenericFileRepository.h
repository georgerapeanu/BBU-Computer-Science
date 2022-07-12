//
// Created by georgerapeanu on 12.06.2022.
//

#ifndef E916_GEORGERAPEANU_1_GENERICFILEREPOSITORY_H
#define E916_GEORGERAPEANU_1_GENERICFILEREPOSITORY_H

#include <vector>
#include <string>

template <class T>
class GenericFileRepository{
    std::vector<T> entities;
    std::string filepath;
public:
    GenericFileRepository(const std::string &filepath);

public:
    void add(const T& entity);
    void update(const T& entity);
    T getById(const T& entity);
    std::vector<T> getAll();

    virtual ~GenericFileRepository();
};


#endif //E916_GEORGERAPEANU_1_GENERICFILEREPOSITORY_H
