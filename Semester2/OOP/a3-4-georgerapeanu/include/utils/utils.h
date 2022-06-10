/*!@file utils.h contains the definitions of various general purpose functions.
 *
 */

#pragma once
#include "../domain/vector.h"

/*!
 * @brief gets a pointer to a new char string having the lowercase version of a given string
 * @param p_s the pointer to the string
 * @param p_error a pointer to the variable that gets the error
 * @return pointer to the new string
 */
char* get_lowercase(const char* p_s, int* p_error);

/*!
 * @brief this function sorts a given vector using the compare function on the range [l,r)
 * @param p_v a pointer to the vector to be sorted
 * @param l the left index
 * @param r the right index
 * @param cmp the compare index which returns 1 if a < b
 */
void sort(vector_t* p_v, int l, int r, int (*cmp)(const void** a, const void** b));

/*!
 * @brief swaps the next cnt_bytes from a and b
 * @param p_a pointer to the first address
 * @param p_b pointer to the second address
 * @param cnt_bytes the number of bytes to swap
 */
void swap(void* p_a, void* p_b, int cnt_bytes);

/*!
 * @brief this function returns a vector structure containing pointers to all tokens in a given string.
 * @param p_s a pointer to the string being processed
 * @param delim a character which is the 'deliminator'
 * @param p_error a pointer to the variable that gets the error
 * @return a pointer to a vector containing pointers to new strings containing the arguments
 */
vector_t* split_string(char* p_s, char delim, int* p_error);