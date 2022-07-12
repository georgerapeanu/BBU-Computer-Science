/*!
 * @file undo_redo_operation.h this file contains the model for an undo_redo operation.
 * This operation consists of 2 operations, one which can undo_operation and one which can redo_operation.
 */
#pragma once
#include "./operation.h"

/*!
 * @brief this is the model for an undo_operation-redo_operation operation
 */
typedef struct{
    //! a pointer to the undo_operation
    operation_t* p_undo_operation;
    //! a pointer to the redo_operation operation
    operation_t* p_redo_operation;
}undo_redo_operation_t;

/*!
 * @brief this function creates an undo_operation-redo_operation operation
 * @param p_undo a pointer to the undo_operation operation
 * @param p_redo a pointer to the redo_operation operation
 * @param p_error a pointer to the variable which receives the error. Can be left NULL.
 * @return a pointer to the undo_operation-redo_operation operation
 */
undo_redo_operation_t* create_undo_redo_operation(operation_t* p_undo, operation_t* p_redo, int* p_error);

/*!
 * @brief this function deletes the memory allocated for an undo_operation-redo_operation operation
 * @param p_operation a pointer to the operation
 */
void delete_undo_redo_operation(undo_redo_operation_t* p_operation);

/*!
 * @brief this function deletes the memory allocated for an undo_operation-redo_operation operation's data, but not the operation itself
 * @param p_operation
 */
void delete_undo_redo_operation_data(undo_redo_operation_t* p_operation);
/*!
 * @brief this function applies the undo_operation operation of a given operation
 * @param p_operation the pointer to the undo_operation-redo_operation operation
 * @param p_error a pointer to the variable which receives the error. Can be left NULL.
 */
void undo_operation(undo_redo_operation_t* p_operation, int* p_error);
/*!
 * @brief this function applies the redo_operation operation of a given operation
 * @param p_operation the pointer to the undo_operation-redo_operation operation
 * @param p_error a pointer to the variable which receives the error. Can be left NULL.
 */
void redo_operation(undo_redo_operation_t* p_operation, int* p_error);