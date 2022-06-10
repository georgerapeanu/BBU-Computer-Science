/*! @file operation_tests.h this file contains the model for the operation_t tests
 *
 */
#pragma once
#include "../../../include/domain/operation.h"
#include <stdlib.h>
#include <assert.h>

static void increment_value(int* p_value, int* p_error){
    (*p_value)++;
}

static void increment_from_args(vector_t* args, int* p_error){
    assert(args->size == 1);
    int* p_value = *(int**) get_position_vector(args, 0, NULL);
    increment_value(p_value, p_error);
}


static void my_free(void** p_elem){
    free(*p_elem);
}

void operation_test_create_delete_operation(){
    int* p_a = (int*)malloc(sizeof(int));
    *p_a = 0;
    vector_t* args = create_vector(sizeof(int*), 0, &my_free, NULL);
    push_back(args, &p_a, NULL);
    operation_t* p_operation = create_operation(&increment_from_args, args, NULL, NULL);
    delete_operation(p_operation);
}

void operation_test_apply(){
    int* p_a = (int*)malloc(sizeof(int));
    *p_a = 0;
    vector_t* args = create_vector(sizeof(int*), 0, &my_free, NULL);
    push_back(args, &p_a, NULL);
    operation_t* p_operation = create_operation(&increment_from_args, args, NULL, NULL);
    apply(p_operation, NULL);
    assert(*p_a == 1);
    apply(p_operation, NULL);
    assert(*p_a == 2);
    delete_operation(p_operation);
}

void operation_test_all(){
    operation_test_apply();
    operation_test_create_delete_operation();
}