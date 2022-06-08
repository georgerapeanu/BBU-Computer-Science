//
// Created by georgerapeanu on 08.06.2022.
//

#ifndef MODEL_GENERALFILEREPOSITORY_H
#define MODEL_GENERALFILEREPOSITORY_H

#include <vector>
#include <string>

template<class T>
class GeneralFileRepository{
    std::vector<T> entities;
    std::string filepath;
    void save();
    void load();
public:
    GeneralFileRepository(const std::string &filepath);
    void add(const T& entity);
    void remove(const T& entity);
    void update(const T& entity);
    std::vector<T> getAll();
    T get(const T& entity);
};


#endif //MODEL_GENERALFILEREPOSITORY_H