/*! @file This file contains the model for a country controller
 *
 */

#pragma once
#include "../../include/domain/errors.h"
#include "../repository/repository.h"
#include "../domain/country.h"
#include "../repository/undo_redo_repository.h"
#include <stdlib.h>

/*!
 * @brief This struct contains the model for a country_controller
 */
typedef struct {
    //! A pointer to the repository which stores the countries.
    repository_t* p_country_repository;
    undo_redo_repository_t* p_undo_redo_repository;
}country_controller_t;

/*!
 * @brief creates a country controller and returns the pointer to it
 * @param p_controller a pointer to the repository containing the countries.
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 * @return pointer to the country controller
 */
country_controller_t* create_country_controller(repository_t* p_repository, undo_redo_repository_t* p_undo_redo_repository, int* p_error);

/*!
 * @brief frees the memory allocated for a country_controller
 * @param p_controller
 */
void delete_country_controller(country_controller_t* p_controller);

/*!
 * @brief Adds a country to the controller. This function should be used by UI only.
 * @param p_controller a pointer to the country controller
 * @param p_country_name a pointer to the country name string
 * @param p_country_continent a pointer to the country continent string
 * @param population the population of the country
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 */
void add_country_ui(country_controller_t* p_controller, const char* p_country_name, const char* p_country_continent, const int population, int make_undo_redo, int* p_error);

/*!
 * @brief Adds a country using arguments contained in a single parameter. This is intended to be used only for undo_operation/redo_operation purposes.
 * @param args a pointer to the vector of arguments this function would normally use
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 */
void add_country_from_args(vector_t* args, int* p_error);

/*!
 * @brief Removes a country based on its name. This is intended to be used by UI only.
 * @param p_controller a pointer to the country controller
 * @param p_country_name a pointer to the string containing the country name
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 */
void remove_country_ui(country_controller_t* p_controller, const char* p_country_name, int make_undo_redo, int* p_error);

/*!
 * @brief Removes a country using arguments contained in a single parameter. This is intended to be used only for undo_operation/redo_operation purposes
 * @param args a pointer to the vector of arguments this function would normally use
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 */
void remove_country_from_args(vector_t* args, int* p_error);

/*!
 * @brief Updates a country based on its name. This is intended to be used by UI only.
 * @param p_controller a pointer to the country controller
 * @param p_country_name a pointer to the string containing the country name
 * @param new_population the new population of the country.
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 */
void update_country_ui(country_controller_t* p_controller, const char* p_country_name, const int new_population, int make_undo_redo, int* p_error);

/*!
 * @brief Updates a country using arguments contained in a single parameter. This is intended to be used for undo_operation/redo_operation purposes only.
 * @param args a pointer to the vector of arguments this function would normally use
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 */
void update_country_from_args(vector_t* args, int* p_error);

/*!
 * @brief migrates population from a country to another. This is intended to be used by UI only.
 * @param p_controller a pointer to the country controller
 * @param p_country_source_name a pointer to the string containing the source country name
 * @param p_country_destination_name a pointer to the string containing the destination country name
 * @param population the population that migrates
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 */
void migrate_ui(country_controller_t* p_controller, const char* p_country_source_name, const char* p_country_destination_name, const int population, int make_undo_redo, int* p_error);

/*!
 * @brief migrates population from a country to another. This is intended to be used for undo_operation/redo_operation purposes only.
 * @param args a pointer to the vector of arguments this function would normally use
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 */
void migrate_from_args(vector_t* args, int* p_error);

/*!
 * @brief This function returns all countries which have given string as substring in their name
 * @param p_controller a pointer to the country controller
 * @param p_name a pointer to the string containing the name
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 * @return a pointer to a vector containing pointer to the valid countries.
 */
vector_t* get_countries_containing_string(country_controller_t* p_controller, const char* p_name, int* p_error);

/*!
 * @brief This function returns all countries which have at least a specified population.
 * @param p_controller a pointer to the country controller.
 * @param population the minimum population a country should have.
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 * @return a pointer to a vector containing pointers to all valid countries.
 */
vector_t* get_countries_with_at_least(country_controller_t* p_controller, const int population, int* p_error);

/*!
 * @brief This functions returns all countries from a continent with at least a specified population.
 * @param p_controller a pointer to the country controller
 * @param p_continent_name a pointer to the string containing the continent name
 * @param population the minimum population a country should have
 * @param p_sort_order a pointer to the string containing the order
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 * @return a pointer to a vector containing pointer to all valid countries.
 */
vector_t* get_countries_from_continent(country_controller_t* p_controller, const char* p_continent_name, const int population, const char* p_sort_order, int* p_error);









