/*! @file vector.h This file contains the model for a dynamic array.
 *  This array is generic, so it holds a void* pointer to a large buffer.
 */

#pragma once

/*! @struct vector_t
 *  @brief Implements a dynamic array.
 *  It is generic, so you can hold any type in it.
 */
typedef struct{
    //! the size of an element of the array. This value assures that the structure is re-usable with any type
    int element_size;
    //! pointer to a bytes buffer which holds the data for the structure. It should be casted to the specific type in order to correctly use the [] operator
    void* elements;
    //! the size of the vector(the number of elements it currently holds)
    int size;
    //! the capacity of the vector(the maximum number of elements it currently can hold)
    int capacity;
    //! a function which is responsible for freeing any memory allocated on the heap for an element.
    void (*free_elem_data)(void* p_elem);
}vector_t;

/*!
 * @brief This function creates a pointer to a new vector_t object.
 * @param element_size the size of a vector element(int bytes)
 * @param initial_size the initial number of elements of the vector
 * @param p_error a pointer to the variable receiving the error code of this function. Can be left NULL
 * @param free_elem_data a pointer to a function responsible for freeing data for a given element(but not the element itself). Can be NULL if no freeing should be applied.
 * @return a pointer to the newly created vector
 */
vector_t* create_vector(int element_size, int initial_size, void (*free_elem_data)(), int* p_error);

/*!
 * @brief This function frees the memory for a vector_t object.
 * @param p_v the pointer to the vector to be freed
 */
void delete_vector(vector_t* p_v);

/*!
 * @brief This function resizes the current vector. It also changes its capacity.
 * @param p_v the pointer to the vector to be resized
 * @param size the new size of the vector
 * @param p_error a pointer to the variable receiving the error code of this function. Can be left NULL
 */
void resize(vector_t* p_v, int size, int* p_error);

/*!
 * @brief This function changes the capacity of the current vector.
 * @param p_v the pointer to the vector to be resized
 * @param capacity the new size of the vector
 * @param p_error a pointer to the variable receiving the error code of this function. Can be left NULL
 */
void change_capacity_vector(vector_t* p_v, int capacity, int* p_error);

/*!
 * @brief This function resizes a given vector. It changes both size, and capacity.
 * Deletes the any elements which do not fit in the new size. Any newly created elements are not initialized to any default value.
 * @param p_v the pointer to the vector on which to push back the element.
 * @param p_element a pointer to the element to be pushed to the back of the vector.
 * @param p_error a pointer to the variable receiving the error code of this function. Can be left NULL.
 */
void push_back(vector_t* p_v, const void* p_element, int* p_error);

/*!
 * @brief This function removes the last element of the vector. It changes only size.
 * @param p_v a pointer to the vector from which the last element is removed
 * @param p_error a pointer to the variable receiving the error code of this function. Can be left NULL.
 */
void pop_back(vector_t* p_v, int* p_error);

/*!
 * @brief gets a pointer to the element from specified position in the given vector
 * @param p_v pointer to the vector that is accessed
 * @param pos the position that is wanted
 * @param p_error a pointer to the variable receiving the error code of this function. Can be left NULL.
 */
void* get_position_vector(const vector_t *p_v, int pos, int *p_error);

/*!
 * @brief sets an element on a given position in the vector to a given element
 * @param p_v pointer to the vector that is modified
 * @param pos the position that will be modified
 * @param p_element pointer to the elemenet with which the position is updated
 * @param p_error a pointer to the variable receiving the error code of this function. Can be left NULL.
 */
void set_position_vector(vector_t *p_v, int pos, const void* p_element, int *p_error);