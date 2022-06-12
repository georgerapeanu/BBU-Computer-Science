//
// Created by georgerapeanu on 09.06.2022.
//

#ifndef PRACTIC_GENERICFILEREPOSITORY_H
#define PRACTIC_GENERICFILEREPOSITORY_H

#include <vector>
#include <fstream>
#include <string>

template <class T>
class GenericFileRepository{
    std::vector<T> entities;
    std::string filepath;

    void load();
    void save();

public:
    GenericFileRepository(const std::string &filepath);
    void add(T elem);
    void update(T elem);
    std::vector<T> getAll();
};

#endif //PRACTIC_GENERICFILEREPOSITORY_H
