/*!
 * @file errors_tests.c this file contains the implementations of the errors tests
 */

#pragma once
#include "../../../include/domain/errors.h"
#include <stdlib.h>
#include <assert.h>


void errors_test_set_error(){
    set_error(NULL, 0);
    int tmp_error = 0;
    set_error(&tmp_error, 1);
    assert(tmp_error == 1);
    set_error(&tmp_error, 0);
    assert(tmp_error == 0);
}

void errors_test_all(){
    errors_test_set_error();
}