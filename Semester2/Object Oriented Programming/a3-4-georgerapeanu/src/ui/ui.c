/*! @file ui.c contains the implementation of ui.h
 *
 */

#pragma once
#include "../../include/ui/ui.h"
#include "../../include/utils/utils.h"
#include "../../include/controller/country_controller.h"
#include "../../include/controller/undo_redo_controller.h"
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * This implementation does exactly what it says it does in ui.h
 */
ui_t* create_ui(country_controller_t* p_controller, undo_redo_controller_t* p_undo_redo_controller ,int* p_error){
    ui_t* p_ui = (ui_t*)malloc(sizeof(ui_t));
    if(p_ui == NULL){
        delete_ui(p_ui);
        set_error(p_error, 1);
        return NULL;
    }
    p_ui->p_controller = p_controller;
    p_ui->p_undo_redo_controller = p_undo_redo_controller;

}
/*
 * This implementation does exactly what it says it does in ui.h
 */
void delete_ui(ui_t* p_ui){
    if(p_ui != NULL){
        free(p_ui);
    }
}

/*!
 * @brief this function displays a country_t object
 * @param p_ui pointer to the ui
 * @param p_country pointer to the country to be displayed
 */
void display_country(ui_t* p_ui, country_t* p_country){
    printf("Country %s from %s with population %d\n",p_country->name, p_country->continent, p_country->population);
}

/*!
 * @brief this function displays a vector of countries
 * @param p_ui a pointer to the ui
 * @param p_countries a pointer to the vector containing the countries
 */
void display_countries(ui_t* p_ui, vector_t* p_countries){
    for(int i = 0;i < p_countries->size;i++){
        country_t* p_country = *(country_t**)get_position_vector(p_countries, i, NULL);
        display_country(p_ui, p_country);
    }
}

/*!
 * @brief display the help for this app
 * @param p_ui pointer to the ui
 */
void display_help(ui_t* p_ui){
    printf("Supported functionalities: \n");
    printf("add country ${name} ${continent} ${population} -> adds a country with specified fields\n");
    printf("update country ${name} ${population} -> updates specified country's population\n");
    printf("remove country ${name} -> removes the country with the given name\n"); ///TODO maybe allow change of name and continent
    printf("migrate from ${source} to ${destination} ${population} -> migrates population from a country to another\n");
    printf("display countries containing ${string} -> displays all countries containing a given string as substring in their name\n");
    printf("display countries with minimum population ${population} -> displays all countries with at least the specified population\n");
    printf("display countries from ${continent} ${min population} ${ascending|descending} ->  displays countries with specified parameters\n");
    printf("help -> displays help menu\n");
    printf("exit -> exits the app\n");
}

/*
 * This implementation does exactly what it says it does in ui.h
 */
/*
 * Supported functionalities:
 * add country ${name} ${continent} ${population} ->5 fields
 * update country ${name} ${population} -> 4 fields
 * remove country ${name} -> 3 fields
 * migrate from ${source} to ${destination} ${population} -> 6 fields
 * display countries containing ${string} -> 4 fields
 * display countries with minimum population ${population} -> 6 fields
 * display countries from ${continent} ${min population} ${ascending|descending} ->  6 fields
 * help -> 1 field
 * exit -> 1 field
*/
void run(ui_t* p_ui){
    char command[100];
    display_help(p_ui);
    while(1){
        int tmp_error = 0;
        char* p_read = fgets(command, 99, stdin);
        int command_len = strlen(command);
        if(p_read == NULL){
            break;
        }
        if(command[command_len - 1] == '\n'){
            command[--command_len] = '\0';
        }
        vector_t* args = split_string(p_read, ' ', &tmp_error);
        if(tmp_error != 0){
            printf("Invalid command\n");
        }else if(args->size == 1){
            char* p_command = *(char**)get_position_vector(args, 0, NULL);
            if(strcmp(p_command, "help") == 0){
                display_help(p_ui);
            }else if(strcmp(p_command, "exit") == 0){
                delete_vector(args);
                break;
            }else if(strcmp(p_command, "undo") == 0) {
                undo(p_ui->p_undo_redo_controller, &tmp_error);
            }else if(strcmp(p_command, "redo") == 0) {
                redo(p_ui->p_undo_redo_controller, &tmp_error);
            }else{
                printf("Invalid command\n");
            }
        }else if(args->size == 3){
            char* p_command = *(char**)get_position_vector(args, 0, NULL);
            char* p_second_arg = *(char**)get_position_vector(args, 1, NULL);
            char* p_third_arg = *(char**)get_position_vector(args, 2, NULL);
            if(strcmp(p_command, "remove") == 0 &&
               strcmp(p_second_arg, "country") == 0){
                remove_country_ui(p_ui->p_controller, p_third_arg, 1, &tmp_error);
            }else{
                printf("Invalid command\n");
            }
        }else if(args->size == 4){
            char* p_command = *(char**)get_position_vector(args, 0, NULL);
            char* p_second_arg = *(char**)get_position_vector(args, 1, NULL);
            char* p_third_arg = *(char**)get_position_vector(args, 2, NULL);
            char* p_fourth_arg = *(char**)get_position_vector(args, 3, NULL);

            if(strcmp(p_command, "update") == 0 && strcmp(p_second_arg, "country") == 0){
                int population = 0;
                if(sscanf(p_fourth_arg, "%d", &population) != 1){
                    tmp_error = 17;
                }else{
                    update_country_ui(p_ui->p_controller, p_third_arg, population, 1, &tmp_error);
                }
            }else if(strcmp(p_command, "display") == 0 && strcmp(p_second_arg, "countries") == 0 && strcmp(p_third_arg, "containing") == 0){
                vector_t* p_countries = get_countries_containing_string(p_ui->p_controller, p_fourth_arg, &tmp_error);
                if(tmp_error != 0){
                    delete_vector(p_countries);
                }else{
                    display_countries(p_ui, p_countries);
                    delete_vector(p_countries);
                }
            }else{
                printf("Invalid command\n");
            }
        }else if(args->size == 5){
            char* p_command = *(char**)get_position_vector(args, 0, NULL);
            char* p_second_arg = *(char**)get_position_vector(args, 1, NULL);
            char* p_third_arg = *(char**)get_position_vector(args, 2, NULL);
            char* p_fourth_arg = *(char**)get_position_vector(args, 3, NULL);
            char* p_fifth_arg = *(char**)get_position_vector(args, 4, NULL);

            if(strcmp(p_command, "add") == 0 && strcmp(p_second_arg, "country") == 0){
                int population = 0;
                if(sscanf(p_fifth_arg, "%d", &population) != 1){
                    tmp_error = 17;
                }else{
                    add_country_ui(p_ui->p_controller, p_third_arg, p_fourth_arg, population, 1, &tmp_error);
                }
            }else{
                printf("Invalid command\n");
            }
        }else if(args->size == 6){
            char* p_command = *(char**)get_position_vector(args, 0, NULL);
            char* p_second_arg = *(char**)get_position_vector(args, 1, NULL);
            char* p_third_arg = *(char**)get_position_vector(args, 2, NULL);
            char* p_fourth_arg = *(char**)get_position_vector(args, 3, NULL);
            char* p_fifth_arg = *(char**)get_position_vector(args, 4, NULL);
            char* p_sixth_arg = *(char**)get_position_vector(args, 5, NULL);

            if(strcmp(p_command, "migrate") == 0 && strcmp(p_second_arg, "from") == 0 &&
               strcmp(p_fourth_arg, "to") == 0){
                int population = 0;
                if(sscanf(p_sixth_arg, "%d", &population) != 1){
                    tmp_error = 17;
                }else{
                    migrate_ui(p_ui->p_controller, p_third_arg, p_fifth_arg, population, 1, &tmp_error);
                }
            }else if(strcmp(p_command, "display") == 0 && strcmp(p_second_arg, "countries") == 0){
                if(strcmp(p_third_arg, "with") == 0 && strcmp(p_fourth_arg, "minimum") == 0 && strcmp(p_fifth_arg, "population") == 0){
                    //display countries from ${continent} ${min population} ${ascending|descending} ->  6 fields
                    int population = 0;
                    if(sscanf(p_sixth_arg, "%d", &population) != 1){
                        tmp_error = 17;
                    }else{
                        vector_t* p_countries = get_countries_with_at_least(p_ui->p_controller, population, &tmp_error);
                        if(tmp_error != 0){
                            delete_vector(p_countries);
                        }else{
                            display_countries(p_ui, p_countries);
                            delete_vector(p_countries);
                        }
                    }
                }else if(strcmp(p_third_arg, "from") == 0){
                    int population = 0;
                    if(sscanf(p_fifth_arg, "%d", &population) != 1){
                        tmp_error = 17;
                    }else{
                        vector_t* p_countries = get_countries_from_continent(p_ui->p_controller, p_fourth_arg, population, p_sixth_arg, &tmp_error);
                        if(tmp_error != 0){
                            delete_vector(p_countries);
                        }else{
                            display_countries(p_ui, p_countries);
                            delete_vector(p_countries);
                        }
                    }
                }else{
                    printf("Invalid command\n");
                }
            }else{
                printf("Invalid command\n");
            }
        }else{
            printf("Invalid command\n");
        }

        if(tmp_error != 0){
            printf("Error %d: %s\n", tmp_error, errors[tmp_error].error_message);
            if(errors[tmp_error].is_fatal){
                printf("FATAL\n");
                return ;
            }
        }
        delete_vector(args);
    }
}