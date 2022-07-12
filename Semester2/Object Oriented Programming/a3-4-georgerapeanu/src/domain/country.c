/*! @file country.c This file contains the implementation of the defined functions for Country.h
 *
 */
#pragma once
#include "../../include/domain/country.h"
#include <string.h>
#include <stdlib.h>
#include "../../include/domain/errors.h"
#include "../../include/utils/utils.h"
/*
 * This implementation does exactly what it says it does in country.h
 */
country_t* create_country(const char* name, const char* continent, int population, int* p_error){
    country_t* p_new_country = (country_t*)malloc(sizeof(country_t));

    if(p_new_country == NULL){
        delete_country(p_new_country);
        set_error(p_error, 1);
        return NULL;
    }

    int tmp_error = 0;
    p_new_country->name = get_lowercase(name, &tmp_error);
    if(tmp_error != 0){
        set_error(p_error, 1);
        delete_country(p_new_country);
        return NULL;
    }

    p_new_country->continent = get_lowercase(continent, &tmp_error);

    if(tmp_error != 0){
        set_error(p_error, 1);
        delete_country(p_new_country);
        return NULL;
    }

    p_new_country->population = population;

    return p_new_country;
}

/*
 * This implementation does exactly what it says it does in country.h
 */
void delete_country(country_t* p_country){
    if(p_country == NULL){
        return;
    }
    delete_country_data(p_country);
    free(p_country);
}
/*
 * This implementation does exactly what it says it does in country.h
 */
void delete_country_data(country_t* p_country){
    if(p_country == NULL){
        return ;
    }
    if(p_country->name != NULL){
        free(p_country->name);
    }
    if(p_country->continent != NULL){
        free(p_country->continent);
    }
}