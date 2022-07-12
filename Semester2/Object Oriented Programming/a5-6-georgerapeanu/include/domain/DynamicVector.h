/*!
 * @file DynamicVector.h this file contains the model for a DynamicVector class
 */

//
// Created by georgerapeanu on 20.03.2022.
//

#ifndef A5_6_GEORGERAPEANU_DYNAMICVECTOR_H
#define A5_6_GEORGERAPEANU_DYNAMICVECTOR_H
#pragma once

//! this is a DynamicVector struct which can hold any type
template<class T>
class DynamicVector{
    //! the array in which the elements are stored
    T* elems;
    //! the current capacity of elems
    unsigned int capacity;
    //! the current size of elems
    unsigned int _size;

    /*!
     * @brief this function is used internally. It changes the size of the used memory to the new capacity.
     * This function is used internally. It changes the size of the used memory to the new capacity.
     * Discards all elements which were after the given capacity.
     * @param capacity the new capacity of the array
     */
    void change_capacity(unsigned int capacity);

public:

    //! Default constructor
    DynamicVector();
    /*! @brief Constructor given a size
     * It creates a vector of a given size and fills it with the default value for T(fills it with T())
     * @param size the size of the vector
     */
    DynamicVector(unsigned int size);
    /*!
     * @brief Constructor given a size and a fill value
     * It creates a vector of a given size and fills it with a given value
     * @param size the size of the vector
     * @param value the value with which the vector is filled
     */
    DynamicVector(unsigned int size, T value);
    //! Copy constructor
    DynamicVector(const DynamicVector<T> &other);
    //! Destructor
    ~DynamicVector();

    DynamicVector<T>& operator = (const DynamicVector &other);

    /*!
     * @brief [] operator for random access. Gets elements as references.
     * @param position the position of the element
     * @return the element on that position as a reference
     * @throws DynamicVectorException if the position is outside the vector
     */
    T& operator [](unsigned int position);
    /*!
     * @brief appends a given element to the back of the array
     * @param elem the element to be appended
     */
    void push_back(T elem);

    T operator [](unsigned int position)const;
    /*!
     * @brief removes the last element from the array.
     */
    void pop_back();
    /*!
     * @brief get the last element as a reference.
     * @return the last element of the vector
     * @throws DynamicVectorException if the vector is empty
     */
    T& back();
    /*!
     * @brief get the size of the vector
     * @return the size of the vector as unsigned int
     */
    unsigned int size()const;
    /*!
     * @brief resizes the vector to a given size
     * Resizes the vector to a given size. Discard all elements that were after the new size. Initializes the new elements with T().
     * @param size the new size of the array
     */
    void resize(unsigned int size);

    /*!
     * @brief removes an element at the specified position
     * @param position the position of the element
     */
    void remove(unsigned int position);

    /*!
     * @brief equality operator between vectors
     * @param other the other movie
     * @return true if they are the same, false otherwise
     */
    bool operator == (const DynamicVector<T> &other)const;
    /*!
     * @brief not equal operator between vectors
     * @param other the other movie
     * @return false if they are the same, true otherwise
     */
    bool operator != (const DynamicVector<T> &other)const;
};

#endif //A5_6_GEORGERAPEANU_DYNAMICVECTOR_H
