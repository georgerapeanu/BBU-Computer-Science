/*! @file repository.h this file contains the model for a general list-based repository
 *
 */

#pragma once
#include "../../include/domain/vector.h"

/*! @struct repository_t
 * @brief This is the model for a repository instance
 */
typedef struct{
    //! a pointer to the vector_t object which holds the elements
    vector_t* p_elements;
}repository_t;

/*!
 * @brief creates a repository object and returns a pointer to it
 * @param element_size the size of a repository element(in bytes)
 * @param p_error a pointer to the variable receiving the error code of this function. Can be left NULL.
 * @param free_element_data a pointer to a function that frees the data for an element(but not the element itself)
 * @return pointer to the newly created repository
 */
repository_t* create_repository(int element_size,void (*free_element_data)(void*), int* p_error);

/*!
 * @brief frees the memory allocated for a given repository
 * @param p_repository a pointer to the repository
 */
void delete_repository(repository_t* p_repository);

/*!
 * @brief adds an element to a given repository
 * @param p_repository a pointer to the repository
 * @param p_element a pointer to the element which is adds to the repository
 * @param p_error a pointer to the variable receiving the error code of this function. Can be left NULL.
 */
void add_repository(repository_t* p_repository, void* p_element, int* p_error);

/*!
 * @brief returns a list of the indexes of elements which match a given filter function.
 * @param p_repository a pointer to the repository
 * @param p_filter_function a filter function which decides which elements are returned. If the function returns 1, the element is added to the answer.
 * The filter function should have 2 arguments, the first one should be the pointer to the repository element, the second one should be any custom function arguments.
 * @param filter_function_args: any custom filter function arguments
 * @param p_error a pointer to the variable receiving the error code of this function. Can be left NULL.
 * @return pointer to a vector that contains the indexes of the elements which are matching a given filter function.
 */
vector_t* filter_repository(repository_t* p_repository, int (*p_filter_function)(void* repository_element, void** args), void **filter_function_args, int* p_error);

/*!
 * @brief updates an element from the repository
 * @param p_repository a pointer to the repository
 * @param position the position of the element which is to be updated
 * @param p_new_element a pointer to the new value of the updated element
 * @param p_error a pointer to the variable receiving the error code of this function. Can be left NULL.
 */
void update_repository(repository_t* p_repository, int position, void* p_new_element, int* p_error);

/*!
 * @brief removes an element from the repository
 * @param p_repository a pointer to the repository
 * @param position the position of the element which is to be removed
 * @param p_error a pointer to the variable receiving the error code of this function. Can be left NULL.
 */
void remove_repository(repository_t* p_repository, int position, int* p_error);

/*!
 * @brief gets an element from a specified position
 * @param p_repository a pointer to the repository
 * @param position the position wanted
 * @return a pointer to the element
 */
void* get_position_repository(repository_t* p_repository, int position, int* p_error);

/*!
 * @brief returns the number of elements the repository currently has
 * @param p_repository a pointer to the repository
 * @return the number of elements the repository contains
 */
int get_repository_size(repository_t* p_repository);

/*!
 * @brief returns the size(in bytes) of a repository element
 * @param p_repository a pointer to the repository
 * @return the size of a repository element
 */
int get_repository_element_size(repository_t* p_repository);