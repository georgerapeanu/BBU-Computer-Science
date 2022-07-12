/*! @file undo_redo_controller.h this file containing the model for implementing the undo_operation-redo_operation controller
 *  This controller is responsible for successfully applying undo_operation and redo_operation functions
 */

#pragma once
#include "../repository/undo_redo_repository.h"
#include "../domain/undo_redo_operation.h"

/*!
 * @brief this struct implements the model for the undo_operation-redo_operation controller
 * The struct will receive operations indirectly. This means, that any controllers that need undo_repository/redo_repository services will push operations directly to the repository used by this controller
 */
typedef struct{
    //! the repository containing undo_operation-redo_operation operations
    undo_redo_repository_t* p_repository;
}undo_redo_controller_t;

/*!
 * @brief this function creates an undo_repository-redo_repository controller instance
 * @param p_repository a pointer to the repository which should be used for storing operations
 * @param p_error a pointer to the variable receiving the error code. Can be left NULL.
 * @return a pointer to an undo_repository-redo_repository controller instance
 */
undo_redo_controller_t* create_undo_redo_controller(undo_redo_repository_t* p_repository, int* p_error);

/*!
 * @brief this function deletes an undo_repository redo_repository controller
 * @param p_undo_redo_controller a pointer to the undo_repository redo_repository controller
 */
void delete_undo_redo_controller(undo_redo_controller_t* p_undo_redo_controller);

/*!
 * @brief this function undoes an operation
 * @param p_undo_redo_controller a pointer to the undo_repository-redo_repository controller
 * @param p_error a pointer to the variable which receives the error code. Can be left NULL.
 */
void undo(undo_redo_controller_t* p_undo_redo_controller, int* p_error);

/*!
 * @brief this function redoes an operation
 * @param p_undo_redo_controller a pointer to the undo_repository-redo_repository controller
 * @param p_error a pointer to the varialbe which receives the error code. Can be left NULL.
 */
void redo(undo_redo_controller_t* p_undo_redo_controller, int* p_error);