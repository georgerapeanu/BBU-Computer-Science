
//
// Created by georgerapeanu on 11.06.2022.
//

#ifndef PRACTICAL_FILEREPOSITORY_H
#define PRACTICAL_FILEREPOSITORY_H

#include <vector>
#include <string>

template<class T>
class FileRepository{
    std::string filepath;
    std::vector<T> entities;

    void load();
    void save();

public:
    FileRepository(const std::string& filepath);

    void add(T entity);
    void update(T entity);
    T getById(const T& entity);
    std::vector<T> getAll();
};


#endif //PRACTICAL_FILEREPOSITORY_H
