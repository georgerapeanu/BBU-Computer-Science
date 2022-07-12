/*! @file errors.c contains the implementation for errors.h
 *
 */

#pragma once
#include "../../include/domain/errors.h"
#include <stdlib.h>

//! this is a vector containing all error codes
const error_t errors[] = {
{"Success!", 0},
{"Unable to allocate more memory(bad_alloc)", 1},
{"Vector element size invalid", 1},
{"Vector size invalid", 1},
{"Vector new capacity is less than old capacity", 1},
{"A pop was attempted on an empty vector", 1},
{"Attempted to access an index which is not in vector", 1},
{"Invalid index in repository", 1},
{"Country with specified name already exists", 0},
{"Country population cannot be negative", 0},
{"Continent does not exist", 0},
{"Country with specified name doesn't exist", 0},
{"Source country cannot be the same with destination country", 0},
{"Source country population is less than migrated population", 0},
{"New population cannot be negative", 0},
{"Sort order invalid", 0},
{"Invalid address", 1},
{"Command does not follow format", 0},
{"Args has wrong size", 1},
{"Cannot undo any further", 0},
{"Cannot redo any further", 0}
};

/*
 * Does exactly what it says it does in errors.h
 */
void set_error(int* p_error, int error_code){
    if(p_error != NULL){
        *p_error = error_code;
    }
}