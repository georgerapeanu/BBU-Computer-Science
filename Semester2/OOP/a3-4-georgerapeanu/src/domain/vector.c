/*! @file vector.c
 * @brief This file contains the implementation for the vector structure implemented in vector.h
 *
 */

#pragma once
#include "../../include/domain/vector.h"
#include "../../include/domain/errors.h"
#include <stdlib.h>
#include <string.h>

/*
 * This implementation does exactly what it says it does in vector.h
 */
vector_t* create_vector(int element_size, int initial_size, void (*free_element_data)(), int* p_error){
    if(element_size < 1){
        set_error(p_error, 2);
        return NULL;
    }
    if(initial_size < 0){
        set_error(p_error, 3);
        return NULL;
    }
    vector_t* p_vector = (vector_t*)malloc(sizeof(vector_t));
    if(p_vector == NULL){
        delete_vector(p_vector);
        set_error(p_error, 1);
        return NULL;
    }
    p_vector->size = initial_size;
    p_vector->element_size = element_size;
    p_vector->capacity = initial_size;
    if(p_vector->capacity < 1){
        p_vector->capacity = 1;
    }
    p_vector->elements = malloc(element_size * p_vector->capacity);
    if(p_vector->elements == NULL){
        delete_vector(p_vector);
        set_error(p_error, 1);
        return NULL;
    }
    p_vector->free_elem_data = free_element_data;
    return p_vector;
}

/*
 * This implementation does exactly what it says it does in vector.h
 */
void delete_vector(vector_t* p_v){
    if(p_v == NULL){
        return;
    }
    if(p_v->free_elem_data != NULL){
        for(int i = 0;i < p_v->size;i++){
            p_v->free_elem_data(get_position_vector(p_v, i, NULL));
        }
    }
    if(p_v->elements != NULL){
        free(p_v->elements);
    }
    free(p_v);
}

/*
 * This implementation does exactly what it says it does in vector.h
 */
void resize(vector_t* p_v, int size, int* p_error){
    if(size < 1){
        set_error(p_error, 3);
        return ;
    }
    void* p_new_elements = malloc(p_v->element_size * size);
    if(p_new_elements == NULL){
        set_error(p_error, 1);
        return ;
    }
    if(p_v->size < size){
        memcpy(p_new_elements, p_v->elements, p_v->element_size * p_v->size);
    }else{
        memcpy(p_new_elements, p_v->elements, p_v->element_size * size);
    }
    free(p_v->elements);
    p_v->size = p_v->capacity = size;
    p_v->elements = p_new_elements;
}

/*
 * This implementation does exactly what it says it does in vector.h
 */
void change_capacity_vector(vector_t* p_v, int capacity, int* p_error){
    if(capacity < p_v->capacity){
        set_error(p_error, 4);
        return;
    }
    void* p_new_elements = malloc(p_v->element_size * capacity);
    if(p_new_elements == NULL){
        set_error(p_error, 1);
        return ;
    }
    memcpy(p_new_elements, p_v->elements, p_v->element_size * p_v->size);
    free(p_v->elements);
    p_v->capacity = capacity;
    p_v->elements = p_new_elements;
}

/*
 * This implementation does exactly what it says it does in vector.h
 */
void push_back(vector_t* p_v, const void* p_element, int* p_error){
    if(p_v->size == p_v->capacity){
        int tmp_error = 0;
        change_capacity_vector(p_v, 2 * p_v->capacity, &tmp_error);
        if(tmp_error != 0){
            set_error(p_error, tmp_error);
            return ;
        }
    }
    memcpy(p_v->elements + p_v->size * p_v->element_size, p_element, p_v->element_size);
    p_v->size++;
}

/*
 * This implementation does exactly what it says it does in vector.h
 */
void pop_back(vector_t* p_v, int* p_error){
    if(p_v->size == 0){
        set_error(p_error, 5);
        return ;
    }
    if(p_v->free_elem_data != NULL){
        p_v->free_elem_data(get_position_vector(p_v, p_v->size - 1, NULL));
    }
    p_v->size--;
}

/*
 * This implementation does exactly what it says it does in vector.h
 */
void* get_position_vector(const vector_t *p_v, int pos, int *p_error){
    if(pos < 0 || pos >= p_v->size){
        set_error(p_error, 6);
        return NULL;
    }
    return p_v->elements + pos * p_v->element_size;
}

/*
 * This implementation does exactly what it says it does in vector.h
 */
void set_position_vector(vector_t *p_v, int pos, const void* p_element, int *p_error){
    if(pos < 0 || pos >= p_v->size){
        set_error(p_error, 6);
        return;
    }
    memcpy(p_v->elements + pos * p_v->element_size, p_element, p_v->element_size);
}





