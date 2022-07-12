/*!
 * @file operation.c this file contains the implementation of the operation structure and its methods
 */

#pragma once
#include "../../include/domain/operation.h"
#include "../../include/domain/errors.h"
#include <stdlib.h>

/*
 * This implementation does exactly what it says it does in operation.h
 */
operation_t* create_operation(void (*function)(vector_t* args, int*p_error), vector_t* args, void (*free_args_data)(vector_t* args), int* p_error){
    operation_t* p_operation = (operation_t*)malloc(sizeof(operation_t));
    if(p_operation == NULL){
        set_error(p_error, 1);
        delete_operation(p_operation);
        return NULL;
    }
    p_operation->args = args;
    p_operation->function = function;
    p_operation->free_args_data = free_args_data;
    return p_operation;
}

/*
 * This implementation does exactly what it says it does in operation.h
 */
void delete_operation(operation_t* p_operation){
    if(p_operation != NULL){
        delete_operation_data(p_operation);
        free(p_operation);
    }
}

/*
 * This implementation does exactly what it says it does in operation.h
 */
void delete_operation_data(operation_t* p_operation){
    if(p_operation->free_args_data != NULL){
        p_operation->free_args_data(p_operation->args);
    }
    delete_vector(p_operation->args);
}

/*
 * This implementation does exactly what it says it does in operation.h
 */
void apply(operation_t* p_operation, int* p_error){
    p_operation->function(p_operation->args, p_error);
}