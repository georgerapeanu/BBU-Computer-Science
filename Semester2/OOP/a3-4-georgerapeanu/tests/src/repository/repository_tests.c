#pragma once
#include "../../include/repository/repository_tests.h"
#include "../../../include/repository/repository.h"
#include "../../../include/domain/vector.h"
#include <stdlib.h>
#include <assert.h>

void repository_test_create_delete_repository(){
    repository_t* p_repository = create_repository(sizeof(int), NULL, NULL);
    assert(p_repository->p_elements->size == 0);
    delete_repository(p_repository);
    delete_repository(NULL);
}

void repository_test_add_repository(){
    repository_t* p_repository = create_repository(sizeof(int), NULL, NULL);
    int a = 0;
    a = 4;
    add_repository(p_repository, &a, NULL);
    a = 5;
    add_repository(p_repository, &a, NULL);
    assert(*(int*)get_position_repository(p_repository, 0, NULL) == 4);
    assert(*(int*)get_position_repository(p_repository, 1, NULL) == 5);
    delete_repository(p_repository);
}

int filter_test(int* a, void** args){
    return *a < ((int*)args)[0];
}

void repository_test_filter_repository(){
    repository_t* p_repository = create_repository(sizeof(int), NULL, NULL);
    int a = 0;
    a = 4;
    add_repository(p_repository, &a, NULL);
    a = 5;
    add_repository(p_repository, &a, NULL);
    a = 1;
    add_repository(p_repository, &a, NULL);

    vector_t* p_v;

    a = 1;
    p_v = filter_repository(p_repository, &filter_test, &a,NULL);
    assert(p_v->size == 0);
    delete_vector(p_v);

    a = 5;
    p_v = filter_repository(p_repository, &filter_test, &a,NULL);
    assert(p_v->size == 2);
    assert(*(int*)get_position_vector(p_v, 0, NULL) == 0);
    assert(*(int*)get_position_vector(p_v, 1, NULL) == 2);
    delete_vector(p_v);

    delete_repository(p_repository);
}

void repository_test_update_repository(){
    repository_t* p_repository = create_repository(sizeof(int), NULL, NULL);
    int a = 0;
    a = 4;
    add_repository(p_repository, &a, NULL);
    a = 5;
    add_repository(p_repository, &a, NULL);
    a = 2;
    update_repository(p_repository, 1, &a, NULL);
    int tmp_error = 0;
    update_repository(p_repository,-1, &a,&tmp_error);
    assert(tmp_error == 7);
    tmp_error = 0;
    assert(*(int*)get_position_repository(p_repository, 0, NULL) == 4);
    assert(*(int*)get_position_repository(p_repository, 1, NULL) == 2);
    delete_repository(p_repository);
}

void repository_test_remove_repository(){
    repository_t* p_repository = create_repository(sizeof(int), NULL, NULL);
    int a = 0;
    a = 4;
    add_repository(p_repository, &a, NULL);
    a = 5;
    add_repository(p_repository, &a, NULL);
    a = 2;
    remove_repository(p_repository, 0, NULL);
    int tmp_error = 0;
    remove_repository(p_repository, 1, &tmp_error);
    assert(tmp_error == 7);
    tmp_error = 0;
    assert(*(int*)get_position_repository(p_repository, 0, NULL) == 5);
    delete_repository(p_repository);
}

void repository_test_get_position_repository(){
    repository_t* p_repository = create_repository(sizeof(int), NULL, NULL);
    int a = 0;
    a = 4;
    add_repository(p_repository, &a, NULL);
    a = 5;
    add_repository(p_repository, &a, NULL);
    assert(*(int*)get_position_repository(p_repository, 0, NULL) == 4);
    assert(*(int*)get_position_repository(p_repository, 1, NULL) == 5);
    delete_repository(p_repository);
}


void repository_test_get_size(){
    repository_t* p_repository = create_repository(sizeof(int), NULL, NULL);
    int a = 0;
    assert(get_repository_size(p_repository) == 0);
    a = 4;
    add_repository(p_repository, &a, NULL);
    assert(get_repository_size(p_repository) == 1);
    a = 5;
    add_repository(p_repository, &a, NULL);
    assert(get_repository_size(p_repository) == 2);
    delete_repository(p_repository);
}

void repository_test_get_element_size(){
    repository_t* p_repository = create_repository(sizeof(int), NULL, NULL);
    int a = 0;
    assert(get_repository_element_size(p_repository) == 4);
    a = 4;
    add_repository(p_repository, &a, NULL);
    assert(get_repository_element_size(p_repository) == 4);
    a = 5;
    add_repository(p_repository, &a, NULL);
    assert(get_repository_element_size(p_repository) == 4);
    delete_repository(p_repository);
}

void repository_test_all(){
    repository_test_create_delete_repository();
    repository_test_add_repository();
    repository_test_filter_repository();
    repository_test_update_repository();
    repository_test_remove_repository();
    repository_test_get_position_repository();
    repository_test_get_size();
    repository_test_get_element_size();
}