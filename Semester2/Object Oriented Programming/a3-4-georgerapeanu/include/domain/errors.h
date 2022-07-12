/*! @file errors.h This file contains the corresponding error messages for various error codes.
 *
 */

#pragma once

/*!
 * this structure is used for errors
 */
typedef struct{
    //*!a pointer to the message corresponding to an error.
    char* error_message;
    //! 1 if the current error is fatal 0 otherwise
    int is_fatal;
}error_t;

//! Array containing all the corresponding messages for each error code.
extern const error_t errors[];

/*!
 * @brief This function sets the error code to a given pointer.
 * @param p_error a pointer to the variable that receives the error code. It can be NULL in case no error is wanted.
 * @param error_code the error code
 */
void set_error(int* p_error, int error_code);
