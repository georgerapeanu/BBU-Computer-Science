/*! @file undo_redo_controller.c this file containing the implementation for implementing the undo_operation-redo_operation controller
 *  This controller is responsible for successfully applying undo_operation and redo_operation functions
 */

#pragma once
#include "../../include/controller/undo_redo_controller.h"
#include "../../include/domain/errors.h"
#include <stdlib.h>

undo_redo_controller_t* create_undo_redo_controller(undo_redo_repository_t* p_repository, int* p_error){
    undo_redo_controller_t* p_controller = (undo_redo_controller_t*)malloc(sizeof(undo_redo_controller_t));
    if(p_controller == NULL){
        set_error(p_error, 1);
        delete_undo_redo_controller(p_controller);
        return NULL;
    }
    p_controller->p_repository = p_repository;
    return p_controller;
}

void delete_undo_redo_controller(undo_redo_controller_t* p_undo_redo_controller){
    if(p_undo_redo_controller != NULL){
        free(p_undo_redo_controller);
    }
}

void undo(undo_redo_controller_t* p_undo_redo_controller, int* p_error){
    undo_repository(p_undo_redo_controller->p_repository, p_error);
}

void redo(undo_redo_controller_t* p_undo_redo_controller, int* p_error){
    redo_repository(p_undo_redo_controller->p_repository, p_error);
}
