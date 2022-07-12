/*! @file ui.h this file contains the model for an ui structure
 *
 */
#pragma once

#include "../controller/country_controller.h"
#include "../controller/undo_redo_controller.h"

/*! @brief this is a model for the ui_t structure
 *
 */
typedef struct{
    //! a pointer to the controller used by the ui
    country_controller_t* p_controller;
    undo_redo_controller_t* p_undo_redo_controller;
}ui_t;

/*
 * Supported functionalities:
 * add country ${name} ${continent} ${population}
 * update country ${name} ${population}
 * remove country ${name}
 * migrate from ${source} to ${destination} ${population}
 * display countries containing ${string}
 * display countries with minimum population ${population}
 * display countries from ${continent} ${min population} ${ascending|descending}
 * help
 * exit
*/

/*!
 * @brief creates ui object
 * @param p_controller pointer to the controller
 * @param p_error pointer to the variable receiving the error code. Can be left NULL.
 */
ui_t* create_ui(country_controller_t* p_controller, undo_redo_controller_t* p_undo_redo_controller ,int* p_error);

/*!
 * frees the memory of a ui_t object
 * @param p_ui pointer to the ui object
 */
void delete_ui(ui_t* p_ui);

/*!
 * @brief the main loop of the ui
 * @param p_ui the pointer to the ui
 */
void run(ui_t* p_ui);