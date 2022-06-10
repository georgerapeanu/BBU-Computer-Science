#pragma once
#include "../../../include/domain/operation.h"
#include "../../../include/domain/undo_redo_operation.h"
#include "../../include/domain/undo_redo_operation_tests.h"
#include <stdlib.h>
#include <assert.h>

static void increment_value(int* p_value, int delta, int* p_error){
    (*p_value) += delta;
}

static void increment_from_args(vector_t* args, int* p_error){
    assert(args->size == 2);
    int* p_value = *(int**) get_position_vector(args, 0, NULL);
    int* p_delta = *(int**) get_position_vector(args, 1, NULL);
    increment_value(p_value, *p_delta, p_error);
}

static void free_args(vector_t* args){
    assert(args->size == 2);
    free(*(int**) get_position_vector(args, 1, NULL));
}


void undo_redo_operation_test_create_delete_undo_redo_operation(){
    int* p_a = (int*)malloc(sizeof(int));
    int* p_delta;
    p_delta = (int*)malloc(sizeof(int));
    *p_delta = -5;
    *p_a = 0;
    vector_t* undo_args = create_vector(sizeof(int*), 0, NULL, NULL);
    push_back(undo_args, &p_a, NULL);
    push_back(undo_args, &p_delta, NULL);
    operation_t* p_undo_operation = create_operation(&increment_from_args, undo_args, &free_args, NULL);

    p_delta = (int*)malloc(sizeof(int));
    *p_delta = 5;
    vector_t* redo_args = create_vector(sizeof(int*), 0, NULL, NULL);
    push_back(redo_args, &p_a, NULL);
    push_back(redo_args, &p_delta, NULL);
    operation_t* p_redo_operation = create_operation(&increment_from_args, redo_args, &free_args, NULL);

    undo_redo_operation_t* p_operation = create_undo_redo_operation(p_undo_operation, p_redo_operation, NULL);
    delete_undo_redo_operation(p_operation);
    free(p_a);
}

void undo_redo_operation_test_undo_redo(){
    int* p_a = (int*)malloc(sizeof(int));
    int* p_delta;
    p_delta = (int*)malloc(sizeof(int));
    *p_delta = -5;
    *p_a = 0;
    vector_t* undo_args = create_vector(sizeof(int*), 0, NULL, NULL);
    push_back(undo_args, &p_a, NULL);
    push_back(undo_args, &p_delta, NULL);
    operation_t* p_undo_operation = create_operation(&increment_from_args, undo_args, &free_args, NULL);

    p_delta = (int*)malloc(sizeof(int));
    *p_delta = 5;
    vector_t* redo_args = create_vector(sizeof(int*), 0, NULL, NULL);
    push_back(redo_args, &p_a, NULL);
    push_back(redo_args, &p_delta, NULL);
    operation_t* p_redo_operation = create_operation(&increment_from_args, redo_args, &free_args, NULL);

    undo_redo_operation_t* p_operation = create_undo_redo_operation(p_undo_operation, p_redo_operation, NULL);
    redo_operation(p_operation, NULL);
    assert(*p_a == 5);
    undo_operation(p_operation, NULL);
    assert(*p_a == 0);
    redo_operation(p_operation, NULL);
    assert(*p_a == 5);
    redo_operation(p_operation, NULL);
    assert(*p_a == 10);
    redo_operation(p_operation, NULL);
    assert(*p_a == 15);
    undo_operation(p_operation, NULL);
    assert(*p_a == 10);
    delete_undo_redo_operation(p_operation);
    free(p_a);
}

void undo_redo_operation_test_all(){
    undo_redo_operation_test_create_delete_undo_redo_operation();
    undo_redo_operation_test_undo_redo();
}