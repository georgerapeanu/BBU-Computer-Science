/*! @file country_controller_tests.h This file contains the models for the test functions for country_controller
 *
 */

#include "../../../include/domain/errors.h"
#include "../../../include/repository/repository.h"
#include "../../../include/domain/country.h"
#include "../../../include/controller/country_controller.h"
#include <stdlib.h>

/*!
 * @brief this function tests the create and delete functionalities for country controller
 */
void country_controller_test_create_delete_country_controller();

/*!
 * @brief this function tests the add from ui country controller function
 */
void country_controller_test_add_country_ui();

/*!
 * @brief this function tests the add from args country controller function
 */
void country_controller_test_add_country_from_args();

/*!
 * @brief this function tests the remove from ui country controller function
 */
void country_controller_test_remove_country_ui();

/*!
 * @brief this function tests the remove from args country controller function
 */
void country_controller_test_remove_country_from_args();

/*!
 * @brief this function tests the remove from args country controller function
 */
void country_controller_test_update_country_ui();

/*!
 * @brief this function tests update country from args country controller function
 */
void country_controller_test_update_country_from_args();

/*!
 * @brief this function tests the migrate ui country controller function
 */
void country_controller_test_migrate_ui();

/*!
 * @brief this function tests migrate from args country controller function
 */
void country_controller_test_migrate_from_args();

/*!
 * @brief this function tests the get countries containing string country controller function
 */
void country_controller_test_get_countries_containing_string();

/*!
 * @brief this function tests the get countries with at least country controller function
 */
void country_controller_test_get_countries_with_at_least();

/*!
 * @brief this function tests the get countries from continent country controller function
 */
void country_controller_test_get_countries_from_continent();

/*!
 * @brief this function runs all country controller tests
 */
void country_controller_test_test_all();
