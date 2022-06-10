/*! @file undo_redo_repository.c this file contains the implementation for a repository responsible for managing undo-redo_ operations
 *
 */

#pragma once
#include "../../include/domain/vector.h"
#include "../../include/domain/undo_redo_operation.h"
#include "../../include/repository/undo_redo_repository.h"
#include "../../include/domain/errors.h"
#include <stdlib.h>
#include <assert.h>

undo_redo_repository_t* create_undo_redo_repository(int* p_error){
    undo_redo_repository_t* p_undo_redo_repository = (undo_redo_repository_t*)malloc(sizeof(undo_redo_repository_t));
    if(p_undo_redo_repository == NULL){
        set_error(p_error, 1);
        delete_undo_redo_repository(p_undo_redo_repository);
        return NULL;
    }
    p_undo_redo_repository->head_idx = -1;
    p_undo_redo_repository->p_operations = create_vector(sizeof(undo_redo_operation_t), 0, &delete_undo_redo_operation_data, NULL);
    return p_undo_redo_repository;
}

void delete_undo_redo_repository(undo_redo_repository_t* p_undo_redo_repository){
    if(p_undo_redo_repository != NULL){
        delete_vector(p_undo_redo_repository->p_operations);
        free(p_undo_redo_repository);
    }
}

void add_undo_repository(undo_redo_repository_t* p_undo_redo_repository, undo_redo_operation_t* p_operation, int* p_error){
    int tmp_error = 0;
    while(p_undo_redo_repository->p_operations->size > 1 + p_undo_redo_repository->head_idx){
        pop_back(p_undo_redo_repository->p_operations, &tmp_error);
        if(tmp_error != 0){
            set_error(p_error, tmp_error);
            return ;
        }
    }
    push_back(p_undo_redo_repository->p_operations, p_operation, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return ;
    }
    p_undo_redo_repository->head_idx++;
}

void undo_repository(undo_redo_repository_t* p_undo_redo_repository, int* p_error){
    if(p_undo_redo_repository->head_idx == -1){
        set_error(p_error, 19);
        return ;
    }
    int tmp_error = 0;
    undo_redo_operation_t* p_operation = get_position_vector(p_undo_redo_repository->p_operations, p_undo_redo_repository->head_idx, &tmp_error);
    assert(tmp_error == 0);
    undo_operation(p_operation, &tmp_error);
    assert(tmp_error == 0);
    p_undo_redo_repository->head_idx--;

}

void redo_repository(undo_redo_repository_t* p_undo_redo_repository, int* p_error){
    if(p_undo_redo_repository->head_idx + 1 == p_undo_redo_repository->p_operations->size){
        set_error(p_error, 20);
        return ;
    }
    p_undo_redo_repository->head_idx++;
    int tmp_error = 0;
    undo_redo_operation_t* p_operation = get_position_vector(p_undo_redo_repository->p_operations, p_undo_redo_repository->head_idx, &tmp_error);
    assert(tmp_error == 0);
    redo_operation(p_operation, &tmp_error);
    assert(tmp_error == 0);
}