/*! @file undo_redo_repository.h this file contains the model for a repository responsible for managing undo-redo operations
 *
 */

#pragma once
#include "../../include/domain/vector.h"
#include "../../include/domain/undo_redo_operation.h"

/*! @struct undo_redo_repository_t
 * @brief This is the model for an undo_redo_repository_t instance
 */
typedef struct{
    //! a pointer to the vector_t object which holds the operations
    vector_t* p_operations;
    //! this keeps track of the current operation
    int head_idx;
}undo_redo_repository_t;

/*!
 * @brief this function creates an undo redo repository
 * @param p_error a pointer to the variable that receives the error code. Can be left NULL.
 * @return a pointer to the undo redo repository created
 */
undo_redo_repository_t* create_undo_redo_repository(int* p_error);

/*!
 * @brief this function frees the memory for a given undo redo repository
 * @param p_undo_redo_repository a pointer to the undo redo repository
 */
void delete_undo_redo_repository(undo_redo_repository_t* p_undo_redo_repository);

/*!
 * @brief add an operation to the repository
 * @param p_undo_redo_repository a pointer to the repository
 * @param p_operation a pointer to the undo redo operation
 * @param p_error a pointer to the variable that receives the error code. Can be left NULL.
 */
void add_undo_repository(undo_redo_repository_t* p_undo_redo_repository, undo_redo_operation_t* p_operation, int* p_error);

/*!
 * @brief this function undoes an operation
 * @param p_undo_redo_repository a pointer to the undo redo repository
 * @param p_error a pointer to the variable that receives the error code. Can be left NULL.
 */
void undo_repository(undo_redo_repository_t* p_undo_redo_repository, int* p_error);

/*!
 * @brief this function redoes an operation
 * @param p_undo_redo_repository
 * @param p_error a pointer to the variable that receives the error code. Can be left NULL.
 */
void redo_repository(undo_redo_repository_t* p_undo_redo_repository, int* p_error);