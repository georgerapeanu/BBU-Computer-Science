/*!
 * @file Repository.h this file contains the model for a general purpose repository
 */

//
// Created by georgerapeanu on 21.03.2022.
//

#ifndef A5_6_GEORGERAPEANU_REPOSITORY_H
#define A5_6_GEORGERAPEANU_REPOSITORY_H
#pragma once
#include "DynamicVector.h"
#include "Exceptions.h"

//! this is the model for a general purpose repository
template<class T>
class Repository{
    //! the vector that stores the elements of the repository
    DynamicVector<T> entities;
public:

    /*!
     * @brief the default constructor of the repository
     * Initializes a repository which holds an empty vector of type T
     */
    Repository();
    /*!
     * @brief the default copy constructor of the repository
     * @param other the repository from which to copy the data
     */
    Repository(const Repository<T> &other);
    /*!
     * @brief the default destructor of the repository
     */
    ~Repository();

    /*!
     * @brief the add method of the repository. Adds an element to the repository
     * @param elem the element to be added
     * @throws RepositoryException if its id is already taken
     */
    void add(const T &elem);

    /*!
     * @brief the update method of the repository. Updates an element of the repository
     * @param elem an element with which to update. It should have the same id as the one to be updated
     * @throws RepositoryException if id doesn't exist
     */
    void update(const T &elem);
    /*!
     * @brief removes an element using the id provided by an element with the same id.
     * @param elem the element to be removed
     * @throws RepositoryException if id doesn't exist
     */
    void remove(const T &elem);
    /*!
     * @brief returns the element with the same id as the element that is provided
     * @param elem the element used to search the id
     * @return the element from the repository with that id
     * @throws RepositoryException if id doesn't exist
     */
    T find(const T &elem);
    /*!
     * @brief gets all elements from the repository
     * @return all elements currently held in the repository
     */
    DynamicVector<T> get_all();
};

#endif //A5_6_GEORGERAPEANU_REPOSITORY_H
