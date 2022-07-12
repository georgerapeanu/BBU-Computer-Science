/*!@file utils.c contains the implementations of various general purpose functions.
 *
 */

#pragma once
#include <stdlib.h>
#include <string.h>
#include "../../include/utils/utils.h"
#include "../../include/domain/errors.h"


/*
 * This implementation does exactly what it says it does in utils.h
 */
char* get_lowercase(const char* p_s, int* p_error){
    char* p_lowercase = (char*)malloc(strlen(p_s) + 1);
    if(p_lowercase == NULL){
        set_error(p_error, 1);
        return NULL;
    }
    strcpy(p_lowercase, p_s);
    for(int i = 0;p_lowercase[i] != '\0';i++){
        if(p_lowercase[i] >= 'A' && p_lowercase[i] <= 'Z'){
            p_lowercase[i] += 'a' - 'A';
        }
    }
    return p_lowercase;
}

/*
 * This implementation does exactly what it says it does in utils.h
 */
void swap(void* p_a, void* p_b, int cnt_bytes){
    for(int i = 0;i < cnt_bytes;i++){
        char tmp = ((char*)p_a)[i];
        ((char*)p_a)[i] = ((char*)p_b)[i];
        ((char*)p_b)[i] = tmp;
    }
}

/*
 * This implementation does exactly what it says it does in utils.h
 */
void sort(vector_t* p_v, int l, int r, int (*cmp)(const void** a, const void** b)){
    if(r - l <= 1){
        return ;
    }
    int cnt = 0;
    for(int i = l + 1;i < r;i++){
        cnt += (*cmp)(get_position_vector(p_v, i, NULL), get_position_vector(p_v, l, NULL));
    }

    swap(get_position_vector(p_v, l, NULL), get_position_vector(p_v, l + cnt,NULL), p_v->element_size);

    int idx = l;
    for(int i = l;i < r;i++){
        if((*cmp)(get_position_vector(p_v, i, NULL), get_position_vector(p_v, l + cnt, NULL)) == 1){
            swap(get_position_vector(p_v, idx, NULL), get_position_vector(p_v, i, NULL), p_v->element_size);
            idx++;
        }
    }

    sort(p_v, l, l + cnt, cmp);
    sort(p_v, l + cnt + 1, r, cmp);
}

/*!
 * @brief this function is responsible for freeing a string from a vector which holds pointers
 * @param p_v
 */
void free_vector_string(void* p_v){
    free(*(char**)p_v);
}

/*
 * This implementation does exactly what it says it does in utils.h
 */
vector_t* split_string(char* p_s, char delim, int* p_error){
    int tmp_error = 0;
    vector_t* p_v = create_vector(sizeof(int*), 0, &free_vector_string, &tmp_error);

    if(tmp_error != 0){
        set_error(p_error, tmp_error);
        delete_vector(p_v);
        return NULL;
    }

    char* p_last = NULL;

    for(char* p_i = p_s;;p_i++){
        if(*p_i == delim || *p_i == '\0'){
            if(p_last == NULL){
                if(p_i != p_s){
                    char* tmp_p = malloc(p_i - p_s + 1);
                    memcpy(tmp_p, p_s, p_i - p_s);
                    tmp_p[p_i - p_s] = '\0';
                    push_back(p_v, &tmp_p, NULL);
                }
            }else{
                if(p_last + 1 < p_i){
                    char* tmp_p = malloc(p_i - p_last);
                    memcpy(tmp_p, p_last + 1, p_i - p_last - 1);
                    tmp_p[p_i - p_last - 1] = '\0';
                    push_back(p_v, &tmp_p, NULL);
                }
            }
            p_last = p_i;
            if(*p_i == '\0'){
                break;
            }
        }
    }

    return p_v;
}