/*! @file operation.h this file containg the model for a struct that can perform a single operation(a 'from_args' function call with parameters)
 *
 */

#pragma once
#include "./vector.h"

/*!
 * @brief This struct contains the model for the operation_t struct
 */
typedef struct {
    //! the function to be applied
    void (*function)(vector_t* args, int* p_error);
    //! the args with which it is called
    vector_t* args;
    //! the function which frees the extra data allocated for args
    void (*free_args_data)(vector_t* args);
}operation_t;

/*!
 * @brief this function creates an operation instance
 * @param function the function which is to be applied
 * @param args the args of the function
 * @param free_args_data the functions which frees the data for given args. Can be left NULL if there is no need for one.
 * @param p_error the pointer to the variable that receives the error. Can be left NULL
 * @return a pointer to the new operation
 */
operation_t* create_operation(void (*function)(vector_t* args, int*p_error), vector_t* args, void (*free_args_data)(vector_t* args), int* p_error);

/*!
 * @brief this function frees the memory for an operation
 * @param p_operation a pointer to the operation to be freed
 */
void delete_operation(operation_t* p_operation);

/*!
 * @brief this function frees the memory allocated for an operation, but not the operation itself
 * @param p_operation a pointer to the operation
 */
void delete_operation_data(operation_t* p_operation);

/*!
 * @brief applies the operation(runs the function with given args).
 * @param p_operation a pointer to the operation
 * @param p_error a pointer to the variable which receives the error. Can be left NULL.
 */
void apply(operation_t* p_operation, int* p_error);