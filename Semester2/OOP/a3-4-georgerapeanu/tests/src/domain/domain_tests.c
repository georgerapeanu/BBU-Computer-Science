/*! @file this file contains the definitions for running all domain tests
 *
 */

#pragma once
#include "../../include/domain/country_tests.h"
#include "../../include/domain/errors_tests.h"
#include "../../include/domain/vector_tests.h"
#include "../../include/domain/operation_tests.h"
#include "../../include/domain/undo_redo_operation_tests.h"

void domain_test_all(){
    country_test_all();
    errors_test_all();
    vector_test_all();
    operation_test_all();
    undo_redo_operation_test_all();
}