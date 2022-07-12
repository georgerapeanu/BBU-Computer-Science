/*! @file the main file for the tests
 *
 */

#pragma once
#include "../include/domain/domain_tests.h"
#include "../include/utils/uitls_tests.h"
#include "../include/repository/repository_tests.h"
#include "../include/controller/country_controller_tests.h"
#include "../include/controller/undo_redo_tests.h"

int main(){
    domain_test_all();
    utils_test_all();
    repository_test_all();
    country_controller_test_test_all();
    undo_redo_test_all();
    return 0;
}