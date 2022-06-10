/*! @file country_controller_tests.c This file contains the implementations for the test functions for country_controller
 *
 */

#pragma once
#include "../../../include/domain/errors.h"
#include "../../../include/repository/repository.h"
#include "../../../include/domain/country.h"
#include "../../../include/controller/country_controller.h"
#include "../../include/controller//country_controller_tests.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*
 * This implementation does exactly what it says it does in country_controller_tests.h
 */
void country_controller_test_create_delete_country_controller(){
    undo_redo_repository_t* p_undo_redo_repository = create_undo_redo_repository(NULL);
    repository_t *p_repository = create_repository(sizeof(country_t), &delete_country_data, NULL);
    country_controller_t* p_controller = create_country_controller(p_repository, p_undo_redo_repository, NULL);
    delete_country_controller(p_controller);
    delete_repository(p_repository);
    delete_undo_redo_repository(p_undo_redo_repository);
}

/*
 * This implementation does exactly what it says it does in country_controller_tests.h
 */
void country_controller_test_add_country_ui(){
    undo_redo_repository_t* p_undo_redo_repository = create_undo_redo_repository(NULL);
    repository_t *p_repository = create_repository(sizeof(country_t), &delete_country_data, NULL);
    country_controller_t* p_controller = create_country_controller(p_repository, p_undo_redo_repository, NULL);
    int tmp_error = 0;
    add_country_ui(p_controller, "aaaaa", "a", 23, 0, &tmp_error);
    assert(tmp_error == 10);
    tmp_error = 0;
    add_country_ui(p_controller, "aaaaa", "america", 23, 0, &tmp_error);
    assert(tmp_error == 0);

    add_country_ui(p_controller, "aaaaa", "europe", 23, 0, &tmp_error);
    assert(tmp_error == 8);
    tmp_error = 0;

    add_country_ui(p_controller, "aaaasaaa", "europe", -1, 0, &tmp_error);
    assert(tmp_error == 9);
    tmp_error = 0;

    vector_t* p_v = get_countries_with_at_least(p_controller, 23, NULL);
    assert(p_v->size == 1);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "aaaaa") == 0);
    delete_vector(p_v);
    delete_country_controller(p_controller);
    delete_repository(p_repository);
    delete_undo_redo_repository(p_undo_redo_repository);
}

/*
 * This implementation does exactly what it says it does in country_controller_tests.h
 */
void country_controller_test_add_country_from_args(){
    undo_redo_repository_t* p_undo_redo_repository = create_undo_redo_repository(NULL);
    repository_t *p_repository = create_repository(sizeof(country_t), &delete_country_data, NULL);
    country_controller_t* p_controller = create_country_controller(p_repository, p_undo_redo_repository, NULL);
    int tmp_error = 0;

    vector_t* args = create_vector(sizeof(int*), 0, NULL, NULL);
    char* p_country_name = malloc(20);
    char* p_continent = malloc(20);
    int* p_population = malloc(sizeof(int));
    int* p_make_undo_redo = malloc(sizeof(int));

    strcpy(p_country_name, "aaaaa");
    strcpy(p_continent, "europe");
    *p_population = 23;
    *p_make_undo_redo = 0;

    add_country_from_args(args, &tmp_error);
    assert(tmp_error == 18);
    tmp_error = 0;

    push_back(args, &p_controller, NULL);
    push_back(args, &p_country_name, NULL);
    push_back(args, &p_continent, NULL);
    push_back(args, &p_population, NULL);
    push_back(args, &p_make_undo_redo, NULL);


    add_country_from_args(args, &tmp_error);
    free(p_population);
    free(p_make_undo_redo);
    free(p_continent);
    free(p_country_name);

    delete_vector(args);
    assert(tmp_error == 0);

    vector_t* p_v = get_countries_with_at_least(p_controller, 23, NULL);
    assert(p_v->size == 1);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "aaaaa") == 0);
    delete_vector(p_v);
    delete_country_controller(p_controller);
    delete_repository(p_repository);
    delete_undo_redo_repository(p_undo_redo_repository);
}

/*
 * This implementation does exactly what it says it does in country_controller_tests.h
 */
void country_controller_test_remove_country_ui(){
    undo_redo_repository_t* p_undo_redo_repository = create_undo_redo_repository(NULL);
    repository_t *p_repository = create_repository(sizeof(country_t), &delete_country_data, NULL);
    country_controller_t* p_controller = create_country_controller(p_repository, p_undo_redo_repository, NULL);
    int tmp_error = 0;
    add_country_ui(p_controller, "aaaaa", "a", 23, 0, &tmp_error);
    assert(tmp_error == 10);
    tmp_error = 0;
    add_country_ui(p_controller, "aaaaa", "america", 23, 0, &tmp_error);
    assert(tmp_error == 0);

    vector_t* p_v = get_countries_with_at_least(p_controller, 23, NULL);
    assert(p_v->size == 1);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "aaaaa") == 0);
    delete_vector(p_v);

    add_country_ui(p_controller, "aaab", "europe", 100, 0, &tmp_error);
    assert(tmp_error == 0);

    p_v = get_countries_with_at_least(p_controller, 23, NULL);
    assert(p_v->size == 2);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "aaaaa") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 1, NULL))->name, "aaab") == 0);
    delete_vector(p_v);

    remove_country_ui(p_controller, "aaaaa", 0, NULL);

    p_v = get_countries_with_at_least(p_controller, 23, NULL);
    assert(p_v->size == 1);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "aaab") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->continent, "europe") == 0);
    assert((*(country_t**)get_position_vector(p_v, 0, NULL))->population == 100);
    delete_vector(p_v);

    remove_country_ui(p_controller, "aaaaa", 0, &tmp_error);
    assert(tmp_error == 11);
    tmp_error = 0;

    delete_country_controller(p_controller);
    delete_repository(p_repository);
    delete_undo_redo_repository(p_undo_redo_repository);
}

/*
 * This implementation does exactly what it says it does in country_controller_tests.h
 */
void country_controller_test_remove_country_from_args(){
    undo_redo_repository_t* p_undo_redo_repository = create_undo_redo_repository(NULL);
    repository_t *p_repository = create_repository(sizeof(country_t), &delete_country_data, NULL);
    country_controller_t* p_controller = create_country_controller(p_repository, p_undo_redo_repository, NULL);
    int tmp_error = 0;
    add_country_ui(p_controller, "aaaaa", "america", 23, 0, &tmp_error);
    assert(tmp_error == 0);

    add_country_ui(p_controller, "aaab", "europe", 100, 0, &tmp_error);
    assert(tmp_error == 0);


    vector_t* args = create_vector(sizeof(void*),0,NULL,NULL);
    char* p_name = malloc(20);
    int* p_make_undo_redo = malloc(sizeof(int));
    strcpy(p_name, "aaab");
    *p_make_undo_redo = 0;


    push_back(args, &p_controller,NULL);
    push_back(args, &p_name,NULL);
    push_back(args, &p_make_undo_redo,NULL);

    remove_country_from_args(args, NULL);

    delete_vector(args);
    free(p_name);
    free(p_make_undo_redo);
    vector_t* p_v;
    p_v = get_countries_with_at_least(p_controller, 23, NULL);
    assert(p_v->size == 1);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "aaaaa") == 0);
    delete_vector(p_v);

    remove_country_ui(p_controller, "aaa", 0, &tmp_error);
    assert(tmp_error == 11);
    tmp_error = 0;

    delete_country_controller(p_controller);
    delete_repository(p_repository);
    delete_undo_redo_repository(p_undo_redo_repository);
}

/*
 * This implementation does exactly what it says it does in country_controller_tests.h
 */
void country_controller_test_update_country_ui(){
    undo_redo_repository_t* p_undo_redo_repository = create_undo_redo_repository(NULL);
    repository_t *p_repository = create_repository(sizeof(country_t), &delete_country_data, NULL);
    country_controller_t* p_controller = create_country_controller(p_repository, p_undo_redo_repository, NULL);
    int tmp_error = 0;
    tmp_error = 0;
    add_country_ui(p_controller, "aaaaa", "america", 23, 0, &tmp_error);
    assert(tmp_error == 0);

    vector_t* p_v = get_countries_with_at_least(p_controller, 23, NULL);
    assert(p_v->size == 1);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "aaaaa") == 0);
    delete_vector(p_v);

    add_country_ui(p_controller, "aaab", "europe", 100, 0, &tmp_error);
    assert(tmp_error == 0);

    p_v = get_countries_with_at_least(p_controller, 23, NULL);
    assert(p_v->size == 2);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "aaaaa") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 1, NULL))->name, "aaab") == 0);
    delete_vector(p_v);

    update_country_ui(p_controller, "aaaaa", 1000, 0, NULL);
    update_country_ui(p_controller, "aaaaa", -1, 0, &tmp_error);
    assert(tmp_error == 9);
    tmp_error = 0;

    p_v = get_countries_with_at_least(p_controller, 150, NULL);
    assert(p_v->size == 1);
    assert((*(country_t**)get_position_vector(p_v, 0, NULL))->population == 1000);
    delete_vector(p_v);
    delete_country_controller(p_controller);
    delete_repository(p_repository);
    delete_undo_redo_repository(p_undo_redo_repository);
}

/*
 * This implementation does exactly what it says it does in country_controller_tests.h
 */
void country_controller_test_update_country_from_args(){
    undo_redo_repository_t* p_undo_redo_repository = create_undo_redo_repository(NULL);
    repository_t *p_repository = create_repository(sizeof(country_t), &delete_country_data, NULL);
    country_controller_t* p_controller = create_country_controller(p_repository, p_undo_redo_repository, NULL);
    int tmp_error = 0;
    tmp_error = 0;
    add_country_ui(p_controller, "aaaaa", "america", 23, 0, &tmp_error);
    assert(tmp_error == 0);

    vector_t* p_v = get_countries_with_at_least(p_controller, 23, NULL);
    assert(p_v->size == 1);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "aaaaa") == 0);
    delete_vector(p_v);

    add_country_ui(p_controller, "aaab", "europe", 100, 0, &tmp_error);
    assert(tmp_error == 0);

    p_v = get_countries_with_at_least(p_controller, 23, NULL);
    assert(p_v->size == 2);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "aaaaa") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 1, NULL))->name, "aaab") == 0);
    delete_vector(p_v);

    vector_t* args = create_vector(sizeof(int*), 0, NULL, NULL);

    char* p_name = malloc(20);
    int* p_population = malloc(sizeof(int));
    int* p_make_undo_redo = malloc(sizeof(int));
    strcpy(p_name, "aaaaa");
    *p_population = 1000;
    *p_make_undo_redo = 0;

    push_back(args, &p_controller, NULL);
    push_back(args, &p_name, NULL);
    push_back(args, &p_population, NULL);
    push_back(args, &p_make_undo_redo, NULL);

    update_country_from_args(args, &tmp_error);

    free(p_name);
    free(p_population);
    free(p_make_undo_redo);

    assert(tmp_error == 0);
    delete_vector(args);

    p_v = get_countries_with_at_least(p_controller, 150, NULL);
    assert(p_v->size == 1);
    assert((*(country_t**)get_position_vector(p_v, 0, NULL))->population == 1000);
    delete_vector(p_v);
    delete_country_controller(p_controller);
    delete_repository(p_repository);
    delete_undo_redo_repository(p_undo_redo_repository);
}

/*
 * This implementation does exactly what it says it does in country_controller_tests.h
 */
void country_controller_test_migrate_ui(){
    undo_redo_repository_t* p_undo_redo_repository = create_undo_redo_repository(NULL);
    repository_t *p_repository = create_repository(sizeof(country_t), &delete_country_data, NULL);
    country_controller_t* p_controller = create_country_controller(p_repository, p_undo_redo_repository, NULL);
    int tmp_error = 0;
    tmp_error = 0;

    add_country_ui(p_controller, "aaaaa", "america", 23, 0, &tmp_error);
    assert(tmp_error == 0);

    add_country_ui(p_controller, "aaab", "europe", 100, 0, &tmp_error);
    assert(tmp_error == 0);

    vector_t* p_v;

    migrate_ui(p_controller, "aaaaa", "aaab",100, 0, &tmp_error);
    assert(tmp_error == 13);
    tmp_error = 0;
    migrate_ui(p_controller, "aaab", "aaaaa",70, 0, &tmp_error);

    p_v = get_countries_containing_string(p_controller, "*", NULL);
    assert(p_v->size == 2);
    assert((*(country_t**)get_position_vector(p_v, 0, NULL))->population == 93);
    assert((*(country_t**)get_position_vector(p_v, 1, NULL))->population == 30);
    delete_vector(p_v);
    delete_country_controller(p_controller);
    delete_repository(p_repository);
    delete_undo_redo_repository(p_undo_redo_repository);
}

/*
 * This implementation does exactly what it says it does in country_controller_tests.h
 */
void country_controller_test_migrate_from_args(){
    undo_redo_repository_t* p_undo_redo_repository = create_undo_redo_repository(NULL);
    repository_t *p_repository = create_repository(sizeof(country_t), &delete_country_data, NULL);
    country_controller_t* p_controller = create_country_controller(p_repository, p_undo_redo_repository, NULL);
    int tmp_error = 0;
    tmp_error = 0;

    add_country_ui(p_controller, "aaaaa", "america", 23, 0, &tmp_error);
    assert(tmp_error == 0);

    add_country_ui(p_controller, "aaab", "europe", 100, 0, &tmp_error);
    assert(tmp_error == 0);

    vector_t* p_v;

    vector_t* args = create_vector(sizeof(int*), 0, NULL, NULL);
    char* p_src_name = malloc(20);
    char* p_dst_name = malloc(20);
    int *p_population = malloc(sizeof(int));
    int *p_make_undo_redo = malloc(sizeof(int));

    strcpy(p_src_name, "aaab");
    strcpy(p_dst_name, "aaaaa");
    *p_make_undo_redo = 0;
    *p_population = 70;

    push_back(args, &p_controller, NULL);
    push_back(args, &p_src_name, NULL);
    push_back(args, &p_dst_name, NULL);
    push_back(args, &p_population, NULL);
    push_back(args, &p_make_undo_redo, NULL);
    migrate_from_args(args, NULL);

    free(p_src_name);
    free(p_dst_name);
    free(p_population);
    free(p_make_undo_redo);
    delete_vector(args);

    p_v = get_countries_containing_string(p_controller, "*", NULL);
    assert(p_v->size == 2);
    assert((*(country_t**)get_position_vector(p_v, 0, NULL))->population == 93);
    assert((*(country_t**)get_position_vector(p_v, 1, NULL))->population == 30);
    delete_vector(p_v);
    delete_country_controller(p_controller);
    delete_repository(p_repository);
    delete_undo_redo_repository(p_undo_redo_repository);
}

/*
 * This implementation does exactly what it says it does in country_controller_tests.h
 */
void country_controller_test_get_countries_containing_string(){
    undo_redo_repository_t* p_undo_redo_repository = create_undo_redo_repository(NULL);
    repository_t *p_repository = create_repository(sizeof(country_t), &delete_country_data, NULL);
    country_controller_t* p_controller = create_country_controller(p_repository, p_undo_redo_repository, NULL);
    int tmp_error = 0;
    tmp_error = 0;

    add_country_ui(p_controller, "China", "asia", 1439, 0, NULL);
    add_country_ui(p_controller, "Brazil", "America", 212, 0, NULL);
    add_country_ui(p_controller, "India", "asia", 1380, 0, NULL);
    add_country_ui(p_controller, "USA", "america", 331, 0, NULL);
    add_country_ui(p_controller, "turkey", "asia", 84, 0, NULL);
    add_country_ui(p_controller, "Ethiopia", "africa", 114, 0, NULL);
    add_country_ui(p_controller, "france", "europe", 65, 0, NULL);
    add_country_ui(p_controller, "germany", "europe", 83, 0, NULL);
    add_country_ui(p_controller, "uk", "europe", 67, 0, NULL);
    add_country_ui(p_controller, "romania", "europe", 19, 0, NULL);



    vector_t* p_v;
    p_v = get_countries_containing_string(p_controller, "*", NULL);
    assert(p_v->size == 10);
    delete_vector(p_v);

    p_v = get_countries_containing_string(p_controller, "a", NULL);
    assert(p_v->size == 8);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "china") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 1, NULL))->name, "brazil") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 2, NULL))->name, "india") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 3, NULL))->name, "usa") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 4, NULL))->name, "ethiopia") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 5, NULL))->name, "france") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 6, NULL))->name, "germany") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 7, NULL))->name, "romania") == 0);
    delete_vector(p_v);

    p_v = get_countries_containing_string(p_controller, "ia", NULL);
    assert(p_v->size == 3);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "india") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 1, NULL))->name, "ethiopia") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 2, NULL))->name, "romania") == 0);
    delete_vector(p_v);

    p_v = get_countries_containing_string(p_controller, "iafsafasfasasfasgasg", NULL);
    assert(p_v->size == 0);
    delete_vector(p_v);

    delete_country_controller(p_controller);
    delete_repository(p_repository);
    delete_undo_redo_repository(p_undo_redo_repository);
}

/*
 * This implementation does exactly what it says it does in country_controller_tests.h
 */
void country_controller_test_get_countries_with_at_least(){
    undo_redo_repository_t* p_undo_redo_repository = create_undo_redo_repository(NULL);
    repository_t *p_repository = create_repository(sizeof(country_t), &delete_country_data, NULL);
    country_controller_t* p_controller = create_country_controller(p_repository, p_undo_redo_repository, NULL);
    int tmp_error = 0;
    tmp_error = 0;

    add_country_ui(p_controller, "China", "asia", 1439, 0, NULL);
    add_country_ui(p_controller, "Brazil", "America", 212, 0, NULL);
    add_country_ui(p_controller, "India", "asia", 1380, 0, NULL);
    add_country_ui(p_controller, "USA", "america", 331, 0, NULL);
    add_country_ui(p_controller, "turkey", "asia", 84, 0, NULL);
    add_country_ui(p_controller, "Ethiopia", "africa", 114, 0, NULL);
    add_country_ui(p_controller, "france", "europe", 65, 0, NULL);
    add_country_ui(p_controller, "germany", "europe", 83, 0, NULL);
    add_country_ui(p_controller, "uk", "europe", 67, 0, NULL);
    add_country_ui(p_controller, "romania", "europe", 19, 0, NULL);



    vector_t* p_v;
    p_v = get_countries_with_at_least(p_controller, 100, NULL);
    assert(p_v->size == 5);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "china") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 1, NULL))->name, "brazil") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 2, NULL))->name, "india") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 3, NULL))->name, "usa") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 4, NULL))->name, "ethiopia") == 0);
    delete_vector(p_v);

    p_v = get_countries_with_at_least(p_controller, 3000000, NULL);
    assert(p_v->size == 0);
    delete_vector(p_v);

    delete_country_controller(p_controller);
    delete_repository(p_repository);
    delete_undo_redo_repository(p_undo_redo_repository);
}

/*
 * This implementation does exactly what it says it does in country_controller_tests.h
 */
void country_controller_test_get_countries_from_continent(){
    undo_redo_repository_t* p_undo_redo_repository = create_undo_redo_repository(NULL);
    repository_t *p_repository = create_repository(sizeof(country_t), &delete_country_data, NULL);
    country_controller_t* p_controller = create_country_controller(p_repository, p_undo_redo_repository, NULL);
    int tmp_error = 0;
    tmp_error = 0;

    add_country_ui(p_controller, "China", "asia", 1439, 0, NULL);
    add_country_ui(p_controller, "Brazil", "America", 212, 0, NULL);
    add_country_ui(p_controller, "India", "asia", 1380, 0, NULL);
    add_country_ui(p_controller, "USA", "america", 331, 0, NULL);
    add_country_ui(p_controller, "turkey", "asia", 84, 0, NULL);
    add_country_ui(p_controller, "Ethiopia", "africa", 114, 0, NULL);
    add_country_ui(p_controller, "france", "europe", 65, 0, NULL);
    add_country_ui(p_controller, "germany", "europe", 83, 0, NULL);
    add_country_ui(p_controller, "uk", "europe", 67, 0, NULL);
    add_country_ui(p_controller, "romania", "europe", 19, 0, NULL);



    vector_t* p_v;
    p_v = get_countries_from_continent(p_controller, "*", 100, "ascending", &tmp_error);
    assert(tmp_error == 0);

    assert(p_v->size == 5);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "ethiopia") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 1, NULL))->name, "brazil") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 2, NULL))->name, "usa") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 3, NULL))->name, "india") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 4, NULL))->name, "china") == 0);
    delete_vector(p_v);

    p_v = get_countries_from_continent(p_controller, "asia", 100, "descending", &tmp_error);
    assert(tmp_error == 0);

    assert(p_v->size == 2);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 0, NULL))->name, "china") == 0);
    assert(strcmp((*(country_t**)get_position_vector(p_v, 1, NULL))->name, "india") == 0);
    delete_vector(p_v);

    delete_country_controller(p_controller);
    delete_repository(p_repository);
    delete_undo_redo_repository(p_undo_redo_repository);
}

/*
 * This implementation does exactly what it says it does in country_controller_tests.h
 */
void country_controller_test_test_all(){
    country_controller_test_create_delete_country_controller();
    country_controller_test_add_country_ui();
    country_controller_test_add_country_from_args();
    country_controller_test_remove_country_ui();
    country_controller_test_remove_country_from_args();
    country_controller_test_update_country_ui();
    country_controller_test_update_country_from_args();
    country_controller_test_migrate_ui();
    country_controller_test_migrate_from_args();
    country_controller_test_get_countries_containing_string();
    country_controller_test_get_countries_with_at_least();
    country_controller_test_get_countries_from_continent();
}
