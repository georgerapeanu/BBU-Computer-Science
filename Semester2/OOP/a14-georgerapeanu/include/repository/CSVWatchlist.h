/*!
 * @file CSVWatchlist.h this is a file that shows the model for a CSVWatchlist
 */

//
// Created by georgerapeanu on 18.04.2022.
//

#ifndef A8_9_GEORGERAPEANU_CSVWATCHLIST_H
#define A8_9_GEORGERAPEANU_CSVWATCHLIST_H
#pragma once
#include "AbstractWatchlist.h"
#include <vector>
#include <string>

template<class T>
class CSVWatchlist: public AbstractWatchlist<T>{
    //! the vector that stores the elements of the repository
    std::vector<T> entities;
    std::string file_path;
public:

    /*!
     * @brief the default constructor of the repository
     * Initializes a repository which holds an empty vector of type T
     * @param file_path this is the path to the file in which to store the data
     */
    CSVWatchlist(const std::string &file_path);

    /*!
     * @brief the default destructor of the repository
     */
    ~CSVWatchlist();

    /*!
     * @brief the add method of the repository. Adds an element to the repository
     * @param elem the element to be added
     * @throws RepositoryException if its id is already taken
     */
    void add(const T &elem)override;

    /*!
     * @brief the update method of the repository. Updates an element of the repository
     * @param elem an element with which to update. It should have the same id as the one to be updated
     * @throws RepositoryException if id doesn't exist
     */
    void update(const T &elem)override;
    /*!
     * @brief removes an element using the id provided by an element with the same id.
     * @param elem the element to be removed
     * @throws RepositoryException if id doesn't exist
     */
    void remove(const T &elem)override;
    /*!
     * @brief returns the element with the same id as the element that is provided
     * @param elem the element used to search the id
     * @return the element from the repository with that id
     * @throws RepositoryException if id doesn't exist
     */
    T find(const T &elem)override;
    /*!
     * @brief gets all elements from the repository
     * @return all elements currently held in the repository
     */
    std::vector<T> get_all()override;

    /*!
     * This function saves the data to a file
     */
    void save()const override;


    /*!
     * This file shows the file
     */
    void display()const override;

};
#endif //A8_9_GEORGERAPEANU_CSVWATCHLIST_H
