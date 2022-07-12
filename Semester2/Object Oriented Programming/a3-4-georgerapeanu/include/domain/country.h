/*! @file country.h This file contains the definitions for the country model.
 *
 */

#pragma once

/*! @struct country_t
 * @brief This struct defined in order to hold all the necessary information for a country.
*/
typedef struct{
    //! This holds a pointer to the start of a char array which contains the name of the country
    char* name;
    //! This holds a pointer to the start of a char array which holds the name of the continent of the country
    char* continent;
    //! This holds the population of the (real) country. Due to the application designed, this will always pe printed in millions
    int population;
}country_t;

/*!
 * @brief This creates a country using the necessary data. It stores its name in lowercase.
 * @param name A pointer to the start of a char array containing the name of the country. The content of the char array is copied in a new dynamically-allocated char array.
 * @param continent A pointer to the start of a char array containing the name of the continent of the country. The content of the char array is copied in a new dynamically-allocated char array.
 * @param population The population of the country
 * @param p_error This is a pointer to the value which receives the error code for this operation(if any).
 *              This can be set to NULL if you do not want the error code.
 * @return a pointer to the new created country
 */
country_t* create_country(const char* name, const char* continent, int population, int* p_error);

/*!
 * @brief This frees the dynamically allocated memory for a given country.
 * @param p_country a pointer to the country for which the memory is freed.
 */
void delete_country(country_t* p_country);

/*!
 * @brief this free the data for a country(but not the country itself)
 * @param p_country a pointer to the country for which the memory is freed.
 */
 void delete_country_data(country_t* p_country);