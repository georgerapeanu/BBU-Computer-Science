/*!
 * @file AbstractRepository.h this file contains the model for a completely abstract repository
 */

//
// Created by georgerapeanu on 18.04.2022.
//

#ifndef A8_9_GEORGERAPEANU_ABSTRACTREPOSITORY_H
#define A8_9_GEORGERAPEANU_ABSTRACTREPOSITORY_H
#pragma once
#include <vector>


//! this is the model for a general purpose repository
template<class T>
class AbstractRepository{
    //! the vector that stores the elements of the repository
public:

    /*!
     * @brief the default constructor of the repository
     */
    AbstractRepository(){
        ;
    }
    /*!
     * @brief the default destructor of the repository
     */
    virtual ~AbstractRepository(){
        //placeholder
    }

    /*!
     * @brief the add method of the repository. Adds an element to the repository
     * @param elem the element to be added
     * @throws RepositoryException if id is taken
     */
    virtual void add(const T &elem) = 0;

    /*!
     * @brief the update method of the repository. Updates an element of the repository
     * @param elem an element with which to update. It should have the same id as the one to be updated
     */
    virtual void update(const T &elem) = 0;
    /*!
     * @brief removes an element using the id provided by an element with the same id.
     * @param elem the element to be removed
     * @throws RepositoryException if id doesn't exist
     */
    virtual void remove(const T &elem) = 0;
    /*!
     * @brief returns the element with the same id as the element that is provided
     * @param elem the element used to search the id
     * @return the element from the repository with that id
     * @throws RepositoryException if id doesn't exist
     */
    virtual T find(const T &elem) = 0;
    /*!
     * @brief gets all elements from the repository
     * @return all elements currently held in the repository
     */
    virtual std::vector<T> get_all() = 0;
};
#endif //A8_9_GEORGERAPEANU_ABSTRACTREPOSITORY_H
