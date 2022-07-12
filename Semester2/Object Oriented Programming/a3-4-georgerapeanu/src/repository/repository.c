/*! @file repository.c This file contains the implementation for repository.h
 *
 */

#pragma once
#include "../../include/repository/repository.h"
#include "../../include/domain/errors.h"
#include "../../include/utils/utils.h"
#include <stdlib.h>

/*
 * This implementation does exactly what it says it does in repository.h
 */
repository_t* create_repository(int element_size,void (*free_element_data)(void*), int* p_error){
    repository_t* p_repository = (repository_t*) malloc(sizeof(repository_t));
    if(p_repository == NULL){
        set_error(p_error, 1);
        delete_repository(p_repository);
        return NULL;
    }
    int tmp_error = 0;
    p_repository->p_elements = create_vector(element_size, 0, free_element_data,&tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        delete_repository(p_repository);
        return NULL;
    }
    return p_repository;
}

/*
 * This implementation does exactly what it says it does in repository.h
 */
void delete_repository(repository_t* p_repository){
    if(p_repository != NULL){
        delete_vector(p_repository->p_elements);
        free(p_repository);
    }
}

/*
 * This implementation does exactly what it says it does in repository.h
 */
void add_repository(repository_t* p_repository, void* p_element, int* p_error){
    push_back(p_repository->p_elements, p_element, p_error);
}

/*
 * This implementation does exactly what it says it does in repository.h
 */
vector_t* filter_repository(repository_t* p_repository, int (*p_filter_function)(void* repository_element, void** args),  void **filter_function_args, int* p_error){
    int tmp_error = 0;
    vector_t* ans = create_vector(4, 0, NULL, &tmp_error);
    if(tmp_error != 0){
        delete_vector(ans);
        set_error(p_error, tmp_error);
        return NULL;
    }
    for(int i = 0;i < p_repository->p_elements->size;i++){
        if((*p_filter_function)(get_position_vector(p_repository->p_elements, i, NULL), filter_function_args) == 1){
            push_back(ans, &i,&tmp_error);
            if(tmp_error != 0){
                delete_vector(ans);
                set_error(p_error, tmp_error);
                return NULL;
            }
        }
    }
    return ans;
}

/*
 * This implementation does exactly what it says it does in repository.h
 */
void update_repository(repository_t* p_repository, int position, void* p_new_element, int* p_error){
    int tmp_error = 0;
    set_position_vector(p_repository->p_elements, position, p_new_element, &tmp_error);
    if(tmp_error != 0){
        if(tmp_error == 6){
            tmp_error = 7;
        }
        set_error(p_error, tmp_error);
        return ;
    }
}

/*
 * This implementation does exactly what it says it does in repository.h
 */
void remove_repository(repository_t* p_repository, int position, int* p_error){
    if(position < 0 || position >= p_repository->p_elements->size){
        set_error(p_error, 7);
        return ;
    }
    int tmp_error = 0;
    for(int i = position;i + 1 < p_repository->p_elements->size;i++){
        swap(get_position_repository(p_repository, i, NULL), get_position_repository(p_repository,i + 1, NULL), p_repository->p_elements->element_size);
    }
    pop_back(p_repository->p_elements, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        return ;
    }
}

/*
 * This implementation does exactly what it says it does in repository.h
 */
void* get_position_repository(repository_t* p_repository, int position, int* p_error){
    return get_position_vector(p_repository->p_elements, position, p_error);
}

/*
 * This implementation does exactly what it says it does in repository.h
 */
int get_repository_size(repository_t* p_repository){
    return p_repository->p_elements->size;
}

/*
 * This implementation does exactly what it says it does in repository.h
 */
int get_repository_element_size(repository_t* p_repository){
    return p_repository->p_elements->element_size;
}
