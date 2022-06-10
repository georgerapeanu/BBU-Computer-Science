/*!
 * @file undo_redo_operation.c this file contains the model for an undo_redo operation.
 * This operation consists of 2 operations, one which can undo_operation and one which can redo_operation.
 */

#pragma once
#include "../../include/domain/undo_redo_operation.h"
#include "../../include/domain/errors.h"
#include <stdlib.h>

/*
 * This implementation does exactly what it says it does in undo_redo_operation.h
 */
undo_redo_operation_t* create_undo_redo_operation(operation_t* p_undo, operation_t* p_redo, int* p_error){
    undo_redo_operation_t* p_operation = (undo_redo_operation_t*) malloc(sizeof(undo_redo_operation_t));
    if(p_operation == NULL){
        set_error(p_error, 1);
        return NULL;
    }
    p_operation->p_redo_operation = p_redo;
    p_operation->p_undo_operation = p_undo;
    return p_operation;
}

/*
 * This implementation does exactly what it says it does in undo_redo_operation.h
 */

void delete_undo_redo_operation(undo_redo_operation_t* p_operation){
    if(p_operation != NULL){
        delete_undo_redo_operation_data(p_operation);
        free(p_operation);
    }
}

/*
 * This implementation does exactly what it says it does in undo_redo_operation.h
 */
void delete_undo_redo_operation_data(undo_redo_operation_t* p_operation){
    delete_operation(p_operation->p_undo_operation);
    delete_operation(p_operation->p_redo_operation);
}

/*
 * This implementation does exactly what it says it does in undo_redo_operation.h
 */
void undo_operation(undo_redo_operation_t* p_operation, int* p_error){
    apply(p_operation->p_undo_operation, p_error);
}

/*
 * This implementation does exactly what it says it does in undo_redo_operation.h
 */
void redo_operation(undo_redo_operation_t* p_operation, int* p_error){
    apply(p_operation->p_redo_operation, p_error);
}