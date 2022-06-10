/*!@file country_tests.c this file contains the tests for country related functions
 *
 */

#pragma once
#include "../../../include/domain/country.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void country_test_create_delete(){
    country_t* p_country = create_country("aaaa", "erer", 23, NULL);
    assert(p_country->population == 23);
    assert(strcmp(p_country->name, "aaaa") == 0);
    assert(strcmp(p_country->continent, "erer") == 0);
    delete_country(p_country);
    delete_country(NULL);
    p_country = create_country("aaaaa", "erere", 23,NULL);
    free(p_country->name);
    p_country->name = NULL;
    free(p_country->continent);
    p_country->continent = NULL;
    delete_country(p_country);
}

void country_test_all(){
    country_test_create_delete();
}