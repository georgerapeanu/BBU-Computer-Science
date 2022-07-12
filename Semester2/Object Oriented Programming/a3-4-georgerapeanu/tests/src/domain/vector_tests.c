#include <assert.h>
#include "../../../include/domain/vector.h"
#include <stdlib.h>

/*! @file vector_tests.c This file contains the implementations for all vector tests
 *
 */


void vector_test_set_position_vector(){
    vector_t* p_v;
    p_v = create_vector(4, 0, NULL, NULL);
    int a = 2;
    push_back(p_v, &a, NULL);
    a = 3;
    push_back(p_v, &a, NULL);
    a = 4;
    push_back(p_v, &a, NULL);

    a = 7;
    set_position_vector(p_v, 1, &a, NULL);
    a = 3;
    set_position_vector(p_v, 2, &a, NULL);

    assert(*(int*)get_position_vector(p_v, 0, NULL) == 2);
    assert(*(int*)get_position_vector(p_v, 1, NULL) == 7);
    assert(*(int*)get_position_vector(p_v, 2, NULL) == 3);

    int tmp_error = 0;
    set_position_vector(p_v, -1, &a, &tmp_error);
    assert(tmp_error == 6);
    tmp_error = 0;
    set_position_vector(p_v, 3, &a, &tmp_error);
    assert(tmp_error == 6);
    tmp_error = 0;

    delete_vector(p_v);
}



void vector_test_get_position_vector(){
    vector_t* p_v;
    p_v = create_vector(4, 0, NULL, NULL);
    int a = 2;
    push_back(p_v, &a, NULL);
    a = 3;
    push_back(p_v, &a, NULL);
    a = 4;
    push_back(p_v, &a, NULL);
    assert(*(int*)get_position_vector(p_v, 0, NULL) == 2);
    assert(*(int*)get_position_vector(p_v, 1, NULL) == 3);
    assert(*(int*)get_position_vector(p_v, 2, NULL) == 4);

    int tmp_error = 0;
    get_position_vector(p_v, -1, &tmp_error);
    assert(tmp_error == 6);
    tmp_error = 0;
    get_position_vector(p_v, 3, &tmp_error);
    assert(tmp_error == 6);
    tmp_error = 0;

    delete_vector(p_v);
}


void vector_test_pop_back(){
    vector_t* p_v;
    p_v = create_vector(4, 0, NULL, NULL);
    int a = 2;
    push_back(p_v, &a, NULL);
    a = 3;
    push_back(p_v, &a, NULL);
    a = 4;
    push_back(p_v, &a, NULL);
    pop_back(p_v, NULL);
    assert(p_v->capacity == 4);
    assert(p_v->size == 2);
    pop_back(p_v, NULL);
    assert(p_v->capacity == 4);
    assert(p_v->size == 1);
    pop_back(p_v, NULL);
    assert(p_v->capacity == 4);
    assert(p_v->size == 0);
    int tmp_error = 0;
    pop_back(p_v, &tmp_error);
    assert(tmp_error == 5);
    assert(p_v->capacity == 4);
    assert(p_v->size == 0);
    delete_vector(p_v);
}


void vector_test_push_back(){
    vector_t* p_v;
    p_v = create_vector(4, 0, NULL,NULL);
    int a = 2;
    push_back(p_v, &a, NULL);
    a = 3;
    push_back(p_v, &a, NULL);
    a = 4;
    push_back(p_v, &a, NULL);
    assert(p_v->capacity == 4);
    assert(p_v->size == 3);
    a = 4;
    push_back(p_v, &a, NULL);
    assert(p_v->capacity == 4);
    assert(p_v->size == 4);
    a = 1;
    push_back(p_v, &a, NULL);
    assert(p_v->capacity == 8);
    assert(p_v->size == 5);
    delete_vector(p_v);
}


void vector_test_change_capacity(){
    vector_t* p_v;
    int tmp_error = 0;
    p_v = create_vector(4, 0, NULL,NULL);
    int a = 2;
    push_back(p_v, &a, NULL);
    a = 3;
    push_back(p_v, &a, NULL);
    change_capacity_vector(p_v, 1, &tmp_error);
    assert(tmp_error == 4);
    tmp_error = 0;
    change_capacity_vector(p_v, 4, &tmp_error);
    assert(tmp_error == 0);
    assert(p_v->capacity == 4);
    assert(p_v->size == 2);

    assert(*(int*)get_position_vector(p_v, 0, NULL) == 2);
    assert(*(int*)get_position_vector(p_v, 1, NULL) == 3);

    delete_vector(p_v);
}


void vector_test_resize(){
    vector_t* p_v;
    int tmp_error = 0;
    p_v = create_vector(4, 0, NULL,NULL);
    assert(p_v->size == 0);
    assert(p_v->capacity == 1);
    assert(p_v->element_size == 4);
    int a = 2;
    push_back(p_v, &a, NULL);
    a = 3;
    push_back(p_v, &a, NULL);

    resize(p_v, -1, &tmp_error);
    assert(tmp_error == 3);
    tmp_error = 0;

    resize(p_v, 4, NULL);

    assert(p_v->size == 4);
    assert(p_v->capacity == 4);
    assert(*(int*)get_position_vector(p_v, 0, NULL) == 2);
    assert(*(int*)get_position_vector(p_v, 1, NULL) == 3);

    resize(p_v, 1, NULL);
    assert(p_v->size == 1);
    assert(p_v->capacity == 1);
    assert(*(int*)get_position_vector(p_v, 0, NULL) == 2);

    delete_vector(p_v);
}


void vector_test_create_delete(){
    int tmp_error = 0;
    vector_t* p_v = NULL;
    tmp_error = 0;
    p_v = create_vector(-1, 10, NULL,&tmp_error);
    assert(tmp_error == 2 && p_v == NULL);
    tmp_error = 0;
    p_v = create_vector(0, 10, NULL, &tmp_error);
    assert(tmp_error == 2 && p_v == NULL);
    tmp_error = 0;
    p_v = create_vector(1, -1, NULL, &tmp_error);
    assert(tmp_error == 3 && p_v == NULL);
    tmp_error = 0;
    p_v = create_vector(1, -1, NULL, &tmp_error);
    assert(tmp_error == 3 && p_v == NULL);
    tmp_error = 0;
    p_v = create_vector(4, 0, NULL, NULL);
    assert(p_v->size == 0);
    assert(p_v->capacity == 1);
    assert(p_v->element_size == 4);
    delete_vector(p_v);
    p_v = create_vector(1, 3, NULL, NULL);
    assert(p_v->size == 3);
    assert(p_v->capacity == 3);
    assert(p_v->element_size == 1);
    delete_vector(p_v);
    delete_vector(NULL);
}


void vector_test_all(){
    vector_test_create_delete();
    vector_test_resize();
    vector_test_change_capacity();
    vector_test_push_back();
    vector_test_pop_back();
    vector_test_set_position_vector();
    vector_test_get_position_vector();
}
