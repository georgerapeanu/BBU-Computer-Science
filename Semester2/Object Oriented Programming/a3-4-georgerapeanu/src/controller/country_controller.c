/*! @file country_controller.c This file contains the implementation for the functions from country_controller.h
 *
 */

#pragma once
#include "../../include/domain/errors.h"
#include "../../include/controller/country_controller.h"
#include "../../include/utils/utils.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*
 * This implementation does exactly what it says it does in country_controller.h
 */
country_controller_t* create_country_controller(repository_t* p_repository, undo_redo_repository_t* p_undo_redo_repository, int* p_error){
    country_controller_t* p_controller = (country_controller_t*)malloc(sizeof(country_controller_t));
    if(p_controller == NULL){
        set_error(p_error, 1);
        delete_country_controller(p_controller);
        return NULL;
    }
    p_controller->p_country_repository = p_repository;
    p_controller->p_undo_redo_repository = p_undo_redo_repository;
    return p_controller;
}

/*
 * This implementation does exactly what it says it does in country_controller.h
 */
void delete_country_controller(country_controller_t* p_controller){
    if(p_controller != NULL){
        free(p_controller);
    }
}

/*!
 * @brief filters countries by checking their exact name
 * @param p_country pointer to a country
 * @param args void** pointer containing only one element which is a pointer to the name to be checked against
 * @return 1 if they are the same, 0 otherwise
 */
int filter_by_exact_name(void* p_country, void** args){
    return strcmp(((country_t*)p_country)->name, ((char*)args)) == 0;
}

/*!
 * @brief returns the index of a country by name in repository.
 * @param p_controller a pointer to the country controller
 * @param p_name a pointer to the string containing the name of the country
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 * @return the country index if it exists, and -1 otherwise(but it also sets p_error to 11)
 */
int get_index_from_name(country_controller_t* p_controller, const char* p_name, int* p_error){
    int tmp_error = 0;
    char* p_lowercase = get_lowercase(p_name, NULL);
    vector_t* p_country_indexes = filter_repository(p_controller->p_country_repository, &filter_by_exact_name, (void**)p_lowercase, &tmp_error);
    free(p_lowercase);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        delete_vector(p_country_indexes);
        return -1;
    }
    if(p_country_indexes->size != 1){
        set_error(p_error, 11);
        delete_vector(p_country_indexes);
        return -1;
    }

    int* p_index = get_position_vector(p_country_indexes, 0, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        delete_vector(p_country_indexes);
        return -1;
    }
    int index = *p_index;
    delete_vector(p_country_indexes);
    return index;
}

/*!
 * @brief adds a country to the controller.
 * @param p_controller a pointer to the country controller
 * @param p_country a pointer to the country to be added.
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 */
void add_country(country_controller_t* p_controller, const country_t* p_country, int* p_error){
    int tmp_error = 0;
    int index = get_index_from_name(p_controller, p_country->name, &tmp_error);
    if(tmp_error != 0){
        if(tmp_error != 11){
            set_error(p_error, tmp_error);
            return ;
        }
        tmp_error = 0;
    }
    if(index != -1){
        set_error(p_error, 8);
        return ;
    }
    add_repository(p_controller->p_country_repository, (void*)p_country, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return ;
    }
}

/*!
 * @brief removes a country from the controller.
 * @param p_controller a pointer to the country controller
 * @param index the index of the country which is removed
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 */
void remove_country(country_controller_t* p_controller, const int index, int* p_error){
    remove_repository(p_controller->p_country_repository, index, p_error);
}

/*!
 * @brief updates a country from the controller.
 * @param p_controller a pointer to the country controller
 * @param index the index of the country which is removed
 * @param p_new_country a pointer to a country object containing the new data
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 */
void update_country(country_controller_t* p_controller, const int index, const country_t* p_new_country, int* p_error){
    int tmp_error = 0;
    void* p_elem = get_position_repository(p_controller->p_country_repository, index, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return ;
    }
    if(p_controller->p_country_repository->p_elements->free_elem_data != NULL){
        p_controller->p_country_repository->p_elements->free_elem_data(p_elem);
    }
    update_repository(p_controller->p_country_repository, index, (void*)p_new_country, p_error);
}

/*!
 * @brief migrates population from a country to another
 * @param p_controller a pointer to the country controller
 * @param src_index the index of the source country
 * @param dst_index the index of the destination country
 * @param population the population that is migrated
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 */
void migrate_country(country_controller_t* p_controller, const int src_index, const int dst_index, const int population, int* p_error){
    if(src_index == dst_index){
        set_error(p_error, 12);
        return ;
    }
    country_t* p_src = NULL;
    country_t* p_dst = NULL;
    int tmp_error = 0;
    p_src = (country_t*)get_position_repository(p_controller->p_country_repository, src_index, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return ;
    }
    p_dst = (country_t*)get_position_repository(p_controller->p_country_repository, dst_index, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return ;
    }
    if(p_src->population < population){
        set_error(p_error, 13);
        return ;
    }
    p_src->population -= population;
    p_dst->population += population;
}

/*!
 * frees the memory allocated for the arguments of an add operation
 * @param args a pointer to the vector containing the arguments
 */
void free_add_country_args(vector_t* args){
    assert(args->size == 5);
    country_controller_t* p_country_controller = *(country_controller_t**)get_position_vector(args, 0, NULL);
    char* p_country_name = *(char**)get_position_vector(args, 1, NULL);
    char* p_continent_name = *(char**)get_position_vector(args, 2, NULL);
    int* p_population = *(int**)get_position_vector(args, 3, NULL);
    int* p_make_undo_redo_operation = *(int**) get_position_vector(args, 4, NULL);
    free(p_country_name);
    free(p_continent_name);
    free(p_population);
    free(p_make_undo_redo_operation);
}


/*!
 * @brief this function frees the memory allocated for the arguments a remove from args operation
 * @param args pointer to the arguments
 */
void free_remove_country_args(vector_t* args){
    assert(args->size == 3);
    country_controller_t* p_country_controller = *(country_controller_t**)get_position_vector(args, 0, NULL);
    char* p_country_name = *(char**)get_position_vector(args, 1, NULL);
    int* p_make_undo_redo_operation = *(int**) get_position_vector(args, 2, NULL);
    free(p_country_name);
    free(p_make_undo_redo_operation);
}

/*!
 * @brief this function frees the memory allocated for arguments for a update from args operation
 * @param args pointer to the arguments
 */
void free_update_country_args(vector_t* args){
    assert(args->size == 4);
    country_controller_t* p_country_controller = *(country_controller_t**)get_position_vector(args, 0, NULL);
    char* p_country_name = *(char**)get_position_vector(args, 1, NULL);
    int* p_population = *(int**)get_position_vector(args, 2, NULL);
    int* p_make_undo_redo_operation = *(int**) get_position_vector(args, 3, NULL);
    free(p_country_name);
    free(p_population);
    free(p_make_undo_redo_operation);
}

void free_migrate_country_args(vector_t* args){
    assert(args->size == 5);
    country_controller_t* p_country_controller = *(country_controller_t**)get_position_vector(args, 0, NULL);
    char* p_country_src = *(char**)get_position_vector(args, 1, NULL);
    char* p_country_dst = *(char**)get_position_vector(args, 2, NULL);
    int* p_population = *(int**)get_position_vector(args, 3, NULL);
    int* p_make_undo_redo_operation = *(int**) get_position_vector(args, 4, NULL);

    free(p_country_src);
    free(p_country_dst);
    free(p_population);
    free(p_make_undo_redo_operation);
}

/*
 * This implementation does exactly what it says it does in country_controller.h
 */
void add_country_ui(country_controller_t* p_controller, const char* p_country_name, const char* p_country_continent, const int population, int make_undo_redo, int* p_error){
    if(population < 0){
        set_error(p_error, 9);
        return ;
    }
    const static char* possible_continents[] = {
            "europe",
            "america",
            "africa",
            "australia",
            "asia"
    };

    int tmp_error = 0;
    char* lowercase_continent = get_lowercase(p_country_continent, &tmp_error);

    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        if(lowercase_continent != NULL){
            free(lowercase_continent);
        }
        return ;
    }

    int ok = 0;
    for(int i = 0;i < 5;i++){
        if(strcmp(possible_continents[i], lowercase_continent) == 0){
            ok = 1;
            break;
        }
    }
    free(lowercase_continent);

    if(ok == 0){
        set_error(p_error, 10);
        return ;
    }

    country_t* p_new_country = create_country(p_country_name, p_country_continent, population, &tmp_error);
    if(tmp_error != 0){
        delete_country(p_new_country);
        set_error(p_error, tmp_error);
        return ;
    }

    add_country(p_controller, p_new_country , &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        delete_country(p_new_country);
        return ;
    }
    free(p_new_country); // we do not want to free any of its char* because they are remembered like that in the repo

    if(make_undo_redo){
        char* p_redo_name = malloc(strlen(p_country_name) + 1);
        char* p_redo_continent = malloc(strlen(p_country_continent) + 1);
        int* p_redo_population = malloc(sizeof(int));
        int* p_redo_make_undo_redo = malloc(sizeof(int));

        strcpy(p_redo_name, p_country_name);
        strcpy(p_redo_continent, p_country_continent);
        *p_redo_population = population;
        *p_redo_make_undo_redo = 0;

        vector_t* redo_args = create_vector(sizeof(int*), 0, NULL ,NULL);
        push_back(redo_args, &p_controller, NULL);
        push_back(redo_args, &p_redo_name, NULL);
        push_back(redo_args, &p_redo_continent, NULL);
        push_back(redo_args, &p_redo_population, NULL);
        push_back(redo_args, &p_redo_make_undo_redo, NULL);
        operation_t* p_redo_operation = create_operation(&add_country_from_args, redo_args, &free_add_country_args, NULL);

        char* p_undo_name = malloc(strlen(p_country_name) + 1);
        int* p_undo_make_undo_redo = malloc(sizeof(int));
        strcpy(p_undo_name, p_country_name);
        *p_undo_make_undo_redo = 0;
        vector_t* undo_args = create_vector(sizeof(int*), 0, NULL ,NULL);
        push_back(undo_args, &p_controller, NULL);
        push_back(undo_args, &p_undo_name, NULL);
        push_back(undo_args, &p_undo_make_undo_redo, NULL);
        operation_t* p_undo_operation = create_operation(&remove_country_from_args, undo_args, &free_remove_country_args, NULL);
        undo_redo_operation_t* p_operation = create_undo_redo_operation(p_undo_operation, p_redo_operation, NULL);
        add_undo_repository(p_controller->p_undo_redo_repository, p_operation, NULL);
        free(p_operation); /// this frees the memory for the operation because its data is stored in the repository
    }
}

/*
 * This implementation does exactly what it says it does in country_controller.h
 */
void add_country_from_args(vector_t* args, int* p_error){
    if(args->size != 5){
        set_error(p_error, 18);
        return ;
    }
    int tmp_error = 0;
    country_controller_t* p_country_controller = *(country_controller_t**)get_position_vector(args, 0, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return;
    }
    char* p_country_name = *(char**)get_position_vector(args, 1, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return;
    }
    char* p_continent_name = *(char**)get_position_vector(args, 2, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return;
    }
    int* p_population = *(int**)get_position_vector(args, 3, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return;
    }
    int* p_make_undo_redo_operation = *(int**) get_position_vector(args, 4, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
    }
    add_country_ui(p_country_controller, p_country_name, p_continent_name, *p_population, *p_make_undo_redo_operation, p_error);
}

/*
 * This implementation does exactly what it says it does in country_controller.h
 */
void remove_country_ui(country_controller_t* p_controller, const char* p_country_name, int make_undo_redo, int* p_error){
    int tmp_error = 0;
    char* p_lowercase_name = get_lowercase(p_country_name, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        if(p_lowercase_name != NULL){
            free(p_lowercase_name);
        }
        return ;
    }

    int index = get_index_from_name(p_controller, p_lowercase_name, &tmp_error);
    free(p_lowercase_name);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return ;
    }
    country_t* p_repo_country = get_position_repository(p_controller->p_country_repository, index, NULL);
    country_t* p_tmp_country = create_country(p_repo_country->name, p_repo_country->continent, p_repo_country->population, NULL);
    remove_country(p_controller, index, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
    }
    else if(make_undo_redo){
        char* p_undo_name = malloc(strlen(p_tmp_country->name) + 1);
        char* p_undo_continent = malloc(strlen(p_tmp_country->continent) + 1);
        int* p_undo_population = malloc(sizeof(int));
        int* p_undo_make_undo_redo = malloc(sizeof(int));

        strcpy(p_undo_name, p_tmp_country->name);
        strcpy(p_undo_continent, p_tmp_country->continent);
        *p_undo_population = p_tmp_country->population;
        *p_undo_make_undo_redo = 0;

        vector_t* undo_args = create_vector(sizeof(int*), 0, NULL ,NULL);
        push_back(undo_args, &p_controller, NULL);
        push_back(undo_args, &p_undo_name, NULL);
        push_back(undo_args, &p_undo_continent, NULL);
        push_back(undo_args, &p_undo_population, NULL);
        push_back(undo_args, &p_undo_make_undo_redo, NULL);
        operation_t* p_undo_operation = create_operation(&add_country_from_args, undo_args, &free_add_country_args, NULL);

        char* p_redo_name = malloc(strlen(p_country_name) + 1);
        int* p_redo_make_undo_redo = malloc(sizeof(int));
        strcpy(p_redo_name, p_country_name);
        *p_redo_make_undo_redo = 0;
        vector_t* redo_args = create_vector(sizeof(int*), 0, NULL ,NULL);
        push_back(redo_args, &p_controller, NULL);
        push_back(redo_args, &p_redo_name, NULL);
        push_back(redo_args, &p_redo_make_undo_redo, NULL);
        operation_t* p_redo_operation = create_operation(&remove_country_from_args, redo_args, &free_remove_country_args, NULL);
        undo_redo_operation_t* p_operation = create_undo_redo_operation(p_undo_operation, p_redo_operation, NULL);
        add_undo_repository(p_controller->p_undo_redo_repository, p_operation, NULL);
        free(p_operation); /// this frees the memory for the operation because its data is stored in the repository
    }
    delete_country(p_tmp_country);
}

/*
 * This implementation does exactly what it says it does in country_controller.h
 */
void remove_country_from_args(vector_t* args, int* p_error){
    if(args->size != 3){
        set_error(p_error, 18);
        return ;
    }
    int tmp_error = 0;
    country_controller_t* p_country_controller = *(country_controller_t**)get_position_vector(args, 0, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return;
    }
    char* p_country_name = *(char**)get_position_vector(args, 1, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return;
    }
    int* p_make_undo_redo_operation = *(int**) get_position_vector(args, 2, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
    }
    remove_country_ui(p_country_controller, p_country_name, *p_make_undo_redo_operation, p_error);
}

/*
 * This implementation does exactly what it says it does in country_controller.h
 */
void update_country_ui(country_controller_t* p_controller, const char* p_country_name, const int new_population, int make_undo_redo_operation, int* p_error){
    if(new_population < 0){
        set_error(p_error, 9);
        return ;
    }
    int tmp_error = 0;

    char* p_lowercase_name = get_lowercase(p_country_name, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        if(p_lowercase_name != NULL){
            free(p_lowercase_name);
        }
        return ;
    }

    int index = get_index_from_name(p_controller, p_lowercase_name, &tmp_error);
    free(p_lowercase_name);

    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return ;
    }
    if(new_population < 0){
        set_error(p_error, 14);
        return ;
    }
    country_t* p_repository_country = get_position_repository(p_controller->p_country_repository, index, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return ;
    }
    country_t* p_old_country = create_country(p_repository_country->name, p_repository_country->continent, p_repository_country->population, &tmp_error);
    country_t* p_new_country = create_country(p_repository_country->name, p_repository_country->continent, new_population, &tmp_error);
    if(tmp_error != 0){
        delete_country(p_new_country);
        set_error(p_error, tmp_error);
        return;
    }
    update_country(p_controller, index, p_new_country, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        delete_country(p_new_country);
        return ;
    }
    if(make_undo_redo_operation){
        char* p_undo_name = malloc(strlen(p_old_country->name) + 1);
        int* p_undo_population = malloc(sizeof(int));
        int* p_undo_make_undo_redo = malloc(sizeof(int));

        strcpy(p_undo_name, p_old_country->name);
        *p_undo_population = p_old_country->population;
        *p_undo_make_undo_redo = 0;

        vector_t* undo_args = create_vector(sizeof(int*), 0, NULL ,NULL);
        push_back(undo_args, &p_controller, NULL);
        push_back(undo_args, &p_undo_name, NULL);
        push_back(undo_args, &p_undo_population, NULL);
        push_back(undo_args, &p_undo_make_undo_redo, NULL);
        operation_t* p_undo_operation = create_operation(&update_country_from_args, undo_args, &free_update_country_args, NULL);

        char* p_redo_name = malloc(strlen(p_new_country->name) + 1);
        int* p_redo_population = malloc(sizeof(int));
        int* p_redo_make_undo_redo = malloc(sizeof(int));
        strcpy(p_redo_name, p_new_country->name);
        *p_redo_population = p_new_country->population;
        *p_redo_make_undo_redo = 0;
        vector_t* redo_args = create_vector(sizeof(int*), 0, NULL ,NULL);
        push_back(redo_args, &p_controller, NULL);
        push_back(redo_args, &p_redo_name, NULL);
        push_back(redo_args, &p_redo_population, NULL);
        push_back(redo_args, &p_redo_make_undo_redo, NULL);
        operation_t* p_redo_operation = create_operation(&update_country_from_args, redo_args, &free_update_country_args, NULL);
        undo_redo_operation_t* p_operation = create_undo_redo_operation(p_undo_operation, p_redo_operation, NULL);
        add_undo_repository(p_controller->p_undo_redo_repository, p_operation, NULL);
        free(p_operation); /// this frees the memory for the operation because its data is stored in the repository
    }
    delete_country(p_old_country);
    free(p_new_country); // we do not want to free any of its char* because they are remembered like that in the repo
}

/*
 * This implementation does exactly what it says it does in country_controller.h
 */
void update_country_from_args(vector_t* args, int* p_error){
    if(args->size != 4){
        set_error(p_error, 18);
        return ;
    }
    int tmp_error = 0;
    country_controller_t* p_country_controller = *(country_controller_t**)get_position_vector(args, 0, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return;
    }
    char* p_country_name = *(char**)get_position_vector(args, 1, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return;
    }

    int* p_population = *(int**)get_position_vector(args, 2, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return;
    }

    int* p_make_undo_redo_operation = *(int**) get_position_vector(args, 3, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
    }

    update_country_ui(p_country_controller, p_country_name, *p_population, *p_make_undo_redo_operation, p_error);
}

/*
 * This implementation does exactly what it says it does in country_controller.h
 */
void migrate_ui(country_controller_t* p_controller, const char* p_country_source_name, const char* p_country_destination_name, const int population, int make_undo_redo_operation ,int* p_error){
    int tmp_error = 0;
    int src_idx = -1;
    int dst_idx = -1;

    if(population < 0){
        set_error(p_error, 9);
        return ;
    }

    src_idx = get_index_from_name(p_controller, p_country_source_name, &tmp_error);

    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return ;
    }

    dst_idx = get_index_from_name(p_controller, p_country_destination_name, &tmp_error);

    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return ;
    }

    migrate_country(p_controller, src_idx, dst_idx, population, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return ;
    }else if(make_undo_redo_operation){
        char* p_undo_src_name = malloc(strlen(p_country_destination_name) + 1);
        char* p_undo_dst_name = malloc(strlen(p_country_source_name) + 1);
        int* p_undo_population = malloc(sizeof(int));
        int* p_undo_make_undo_redo = malloc(sizeof(int));

        strcpy(p_undo_src_name, p_country_destination_name);
        strcpy(p_undo_dst_name, p_country_source_name);
        *p_undo_population = population;
        *p_undo_make_undo_redo = 0;

        vector_t* undo_args = create_vector(sizeof(int*), 0, NULL ,NULL);
        push_back(undo_args, &p_controller, NULL);
        push_back(undo_args, &p_undo_src_name, NULL);
        push_back(undo_args, &p_undo_dst_name, NULL);
        push_back(undo_args, &p_undo_population, NULL);
        push_back(undo_args, &p_undo_make_undo_redo, NULL);
        operation_t* p_undo_operation = create_operation(&migrate_from_args, undo_args, &free_migrate_country_args, NULL);

        char* p_redo_src_name = malloc(strlen(p_country_source_name) + 1);
        char* p_redo_dst_name = malloc(strlen(p_country_destination_name) + 1);
        int* p_redo_population = malloc(sizeof(int));
        int* p_redo_make_undo_redo = malloc(sizeof(int));

        strcpy(p_redo_src_name, p_country_source_name);
        strcpy(p_redo_dst_name, p_country_destination_name);
        *p_redo_population = population;
        *p_redo_make_undo_redo = 0;

        vector_t* redo_args = create_vector(sizeof(int*), 0, NULL ,NULL);
        push_back(redo_args, &p_controller, NULL);
        push_back(redo_args, &p_redo_src_name, NULL);
        push_back(redo_args, &p_redo_dst_name, NULL);
        push_back(redo_args, &p_redo_population, NULL);
        push_back(redo_args, &p_redo_make_undo_redo, NULL);
        operation_t* p_redo_operation = create_operation(&migrate_from_args, redo_args, &free_migrate_country_args, NULL);

        undo_redo_operation_t* p_operation = create_undo_redo_operation(p_undo_operation, p_redo_operation, NULL);
        add_undo_repository(p_controller->p_undo_redo_repository, p_operation, NULL);
        free(p_operation); /// this frees the memory for the operation because its data is stored in the repository
    }
}

/*
 * This implementation does exactly what it says it does in country_controller.h
 */
void migrate_from_args(vector_t* args, int* p_error){
    if(args->size != 5){
        set_error(p_error, 18);
        return ;
    }
    int tmp_error = 0;
    country_controller_t* p_country_controller = *(country_controller_t**)get_position_vector(args, 0, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return;
    }

    char* p_country_src = *(char**)get_position_vector(args, 1, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return;
    }

    char* p_country_dst = *(char**)get_position_vector(args, 2, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return;
    }
    if(p_country_dst == NULL){
        set_error(p_error, 16);
        return ;
    }

    int* p_population = *(int**)get_position_vector(args, 3, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return;
    }
    if(p_population == NULL){
        set_error(p_error, 16);
        return ;
    }

    int* p_make_undo_redo_operation = *(int**) get_position_vector(args, 4, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
    }

    migrate_ui(p_country_controller, p_country_src, p_country_dst, *p_population, *p_make_undo_redo_operation, p_error);
}


/*!
 * @brief returns a vector containing the pointers to the countries corresponding to the indexes from a given vector
 * @param p_controller pointer to the country controller
 * @param p_indexes pointer to the vector containing the indexes
 * @param p_error pointer to the variable that receives the error variable. Can be left NULL
 * @return pointer to a vector containing pointers to countries.
 */
vector_t* get_p_countries_from_p_indexes(const country_controller_t* p_controller, vector_t* p_indexes, int* p_error){
    int tmp_error = 0;
    vector_t* p_countries = create_vector(sizeof(void*), 0, NULL, &tmp_error);

    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        delete_vector(p_countries);
        return NULL;
    }

    for(int i = 0;i < p_indexes->size;i++){
        int* p_idx = (int*)get_position_vector(p_indexes, i, &tmp_error);
        if(tmp_error != 0){
            set_error(p_error, tmp_error);
            delete_vector(p_countries);
            return NULL;
        }
        int idx = *p_idx;
        country_t* p_country = get_position_repository(p_controller->p_country_repository, idx, &tmp_error);
        if(tmp_error != 0){
            set_error(p_error, tmp_error);
            delete_vector(p_countries);
            return NULL;
        }
        push_back(p_countries, &p_country, &tmp_error);
        if(tmp_error != 0){
            set_error(p_error, tmp_error);
            delete_vector(p_countries);
            return NULL;
        }
    }

    return p_countries;
}

/*!
 * @brief returns 1 if the given country contains a given string in its name and 0 otherwise
 * @param p_country pointer to the country
 * @param args a pointer to an array of pointers containing a single element which points to the string which is to be checked against
 * @return 1 if the string is included, 0 otherwise
 */
int filter_contains_string(country_t* p_country, void** args){
    return strstr(p_country->name, (char*)args) != NULL;
}

/*
 * This implementation does exactly what it says it does in country_controller.h
 */
vector_t* get_countries_containing_string(country_controller_t* p_controller, const char* p_name, int* p_error){
    int tmp_error = 0;
    char* p_lowercase_name = get_lowercase(p_name, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        if(p_lowercase_name != NULL){
            free(p_lowercase_name);
        }
        return NULL;
    }
    if(strcmp(p_lowercase_name, "*") == 0){
        strcpy(p_lowercase_name, "");
    }
    vector_t* p_country_indexes = filter_repository(p_controller->p_country_repository, &filter_contains_string, (void**)p_lowercase_name, &tmp_error);
    free(p_lowercase_name);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        delete_vector(p_country_indexes);
        return NULL;
    }

    vector_t* p_countries = get_p_countries_from_p_indexes(p_controller, p_country_indexes, p_error);
    delete_vector(p_country_indexes);
    return p_countries;
}

/*!
 * @brief returns 1 if the given country has more population than a given amount
 * @param p_country pointer to the country
 * @param args a pointer to an array of pointers containing a single element which points to an int which is the population to be checked against
 * @return 1 if the string is included, 0 otherwise
 */
int filter_at_least(country_t* p_country, void** args){
    return p_country->population >= *(int*)args;
}

/*
 * This implementation does exactly what it says it does in country_controller.h
 */
vector_t* get_countries_with_at_least(country_controller_t* p_controller, const int population, int* p_error){
    int tmp_error = 0;
    vector_t* p_country_indexes = filter_repository(p_controller->p_country_repository, &filter_at_least, (void**)&population, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        delete_vector(p_country_indexes);
        return NULL;
    }
    vector_t* p_countries = get_p_countries_from_p_indexes(p_controller, p_country_indexes, p_error);
    delete_vector(p_country_indexes);
    return p_countries;
}

/*!
 * @brief returns 1 if the given country's continent matches a string, and 0 otherwise
 * @param p_country pointer to the country
 * @param args a pointer to an array of pointers containing a single element which points to the string which is to be checked against
 * @return 1 if the string is included, 0 otherwise
 */
int filter_matches_string_continent_and_population(country_t* p_country, void** args){
    if(strcmp((char*)(args[0]),"") == 0 || strcmp(p_country->continent, (char*)args[0]) == 0){
        if(p_country->population >= *(int*)args[1]){
            return 1;
        }
    }
    return 0;
}

/*!
 * @brief comparator for sorting countries ascendingly according to population
 * @param a pointer to the first country
 * @param b pointer to the second country
 * @return return 0 if a has more population than b, 1 otherwise
 */
int cmp_ascending(const country_t** a, const country_t** b){
    return (*a)->population < (*b)->population;
}

/*!
 * @brief comparator for sorting countries descendingly according to population
 * @param a pointer to a pointer to the first country
 * @param b pointer to a pointer to the second country
 * @return return 0 if a has more population than b, 1 otherwise
 */
int cmp_descending(const country_t** a, const country_t** b){
    return (*a)->population > (*b)->population;
}
/*
 * This implementation does exactly what it says it does in country_controller.h
 */
vector_t* get_countries_from_continent(country_controller_t* p_controller, const char* p_continent_name, const int population, const char* p_sort_order, int* p_error){
    int tmp_error = 0;

    char* p_lowercase_sort_order = get_lowercase(p_sort_order, &tmp_error);

    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return NULL;
    }

    int order_type = -1;

    if(strcmp(p_lowercase_sort_order, "ascending") == 0){
        order_type = 0;
    }else if(strcmp(p_lowercase_sort_order, "descending") == 0){
        order_type = 1;
    }else{
        free(p_lowercase_sort_order);
        set_error(p_error, 15);
        return NULL;
    }

    free(p_lowercase_sort_order);

    char* p_lowercase_name = get_lowercase(p_continent_name, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        if(p_lowercase_name != NULL){
            free(p_lowercase_name);
        }
        return NULL;
    }
    if(strcmp(p_lowercase_name,"*") == 0){
        strcpy(p_lowercase_name,"");
    }

    void** args = malloc(sizeof(void*) * 2);
    args[0] = p_lowercase_name;
    args[1] = &population;
    vector_t* p_country_indexes = filter_repository(p_controller->p_country_repository, &filter_matches_string_continent_and_population, args, &tmp_error);
    free(args);
    vector_t* p_countries = get_p_countries_from_p_indexes(p_controller, p_country_indexes, &tmp_error);
    delete_vector(p_country_indexes);
    free(p_lowercase_name);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        delete_vector(p_countries);
        return NULL;
    }

    if(order_type == 0){
        sort(p_countries, 0, p_countries->size, &cmp_ascending);
    }else{
        sort(p_countries, 0, p_countries->size, &cmp_descending);
    }
    return p_countries;
}









