/*!@file utils_tests.c contains the implementation for the utils_test functions
 *
 */

#pragma once

#include "../../../include/utils/utils.h"
#include "../../../include/domain/vector.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void utils_test_get_lowercase(){
    char* p_s = get_lowercase("asf  aASFAFASFasfasfsafASFASFavbvaCCzzZZ^^", NULL);
    assert(strcmp(p_s,"asf  aasfafasfasfasfsafasfasfavbvacczzzz^^") == 0);
    free(p_s);
}

static int normal_int_cmp(int* p_a, int* p_b){
    return *p_a < *p_b;
}

void utils_test_sort(){
    vector_t* p_v = create_vector(4, 0, NULL,NULL);
    int a = 0;
    a = 1;
    push_back(p_v, &a, NULL);
    a = 59;
    push_back(p_v, &a, NULL);
    a = 2;
    push_back(p_v, &a, NULL);
    a = 3;
    push_back(p_v, &a, NULL);
    a = 0;
    push_back(p_v, &a, NULL);
    a = 6;
    push_back(p_v, &a, NULL);
    a = 8;
    push_back(p_v, &a, NULL);
    a = 1;
    push_back(p_v, &a, NULL);
    sort(p_v, 0, p_v->size, &normal_int_cmp);

    assert(*(int*)get_position_vector(p_v, 0, NULL) == 0);
    assert(*(int*)get_position_vector(p_v, 1, NULL) == 1);
    assert(*(int*)get_position_vector(p_v, 2, NULL) == 1);
    assert(*(int*)get_position_vector(p_v, 3, NULL) == 2);
    assert(*(int*)get_position_vector(p_v, 4, NULL) == 3);
    assert(*(int*)get_position_vector(p_v, 5, NULL) == 6);
    assert(*(int*)get_position_vector(p_v, 6, NULL) == 8);
    assert(*(int*)get_position_vector(p_v, 7, NULL) == 59);

    delete_vector(p_v);
}

void utils_test_swap(){
    char *p1 = malloc(12);
    char *p2 = malloc(12);
    strcpy(p1, "ASFAsafaafa");
    strcpy(p2, "ooooooooooo");
    swap(p1, p2, 5);
    assert(strcmp(p1, "oooooafaafa") == 0);
    assert(strcmp(p2, "ASFAsoooooo") == 0);
    free(p1);
    free(p2);
}

void utils_test_split_string(){
    vector_t* p_v = split_string("   this is my   test a   123   ", ' ', NULL);
    assert(p_v->size == 6);
    assert(strcmp(*(char**)get_position_vector(p_v, 0, NULL), "this") == 0);
    assert(strcmp(*(char**)get_position_vector(p_v, 1, NULL), "is") == 0);
    assert(strcmp(*(char**)get_position_vector(p_v, 2, NULL), "my") == 0);
    assert(strcmp(*(char**)get_position_vector(p_v, 3, NULL), "test") == 0);
    assert(strcmp(*(char**)get_position_vector(p_v, 4, NULL), "a") == 0);
    assert(strcmp(*(char**)get_position_vector(p_v, 5, NULL), "123") == 0);
    delete_vector(p_v);
    p_v = split_string("his,isaa,my,test a,,,123", ',', NULL);
    assert(p_v->size == 5);
    assert(strcmp(*(char**)get_position_vector(p_v, 0, NULL), "his") == 0);
    assert(strcmp(*(char**)get_position_vector(p_v, 1, NULL), "isaa") == 0);
    assert(strcmp(*(char**)get_position_vector(p_v, 2, NULL), "my") == 0);
    assert(strcmp(*(char**)get_position_vector(p_v, 3, NULL), "test a") == 0);
    assert(strcmp(*(char**)get_position_vector(p_v, 4, NULL), "123") == 0);
    delete_vector(p_v);
}

void utils_test_all(){
    utils_test_split_string();
    utils_test_get_lowercase();
    utils_test_swap();
    utils_test_sort();
}
