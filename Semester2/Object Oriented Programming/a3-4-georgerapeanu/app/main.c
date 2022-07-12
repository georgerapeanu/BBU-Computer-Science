/*! @file main.c this is where the application starts
 *
 */
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "../include/repository/repository.h"
#include "../include/domain/country.h"
#include "../include/controller/country_controller.h"
#include "../include/ui/ui.h"

int main(){
    repository_t* p_repository = create_repository(sizeof(country_t),&delete_country_data,NULL);
    undo_redo_repository_t* p_undo_redo_repository = create_undo_redo_repository(NULL);
    country_controller_t* p_controller = create_country_controller(p_repository, p_undo_redo_repository, NULL);
    undo_redo_controller_t* p_undo_redo_controller = create_undo_redo_controller(p_undo_redo_repository, NULL);
    ui_t* p_ui = create_ui(p_controller, p_undo_redo_controller, NULL);
    if(p_repository == NULL || p_controller == NULL || p_ui == NULL || p_undo_redo_repository == NULL || p_undo_redo_controller == NULL){
        printf("Application failed to start\n");
    }


    add_country_ui(p_controller, "China", "asia", 1439, 0, NULL);
    add_country_ui(p_controller, "Brazil", "America", 212, 0, NULL);
    add_country_ui(p_controller, "India", "asia", 1380, 0, NULL);
    add_country_ui(p_controller, "USA", "america", 331,0, NULL);
    add_country_ui(p_controller, "turkey", "asia", 84, 0, NULL);
    add_country_ui(p_controller, "Ethiopia", "africa", 114, 0, NULL);
    add_country_ui(p_controller, "france", "europe", 65,0, NULL);
    add_country_ui(p_controller, "germany", "europe", 83, 0, NULL);
    add_country_ui(p_controller, "uk", "europe", 67, 0, NULL);
    add_country_ui(p_controller, "romania", "europe", 19, 0, NULL);

    run(p_ui);
    delete_ui(p_ui);
    delete_country_controller(p_controller);
    delete_repository(p_repository);
    delete_undo_redo_repository(p_undo_redo_repository);
    delete_undo_redo_controller(p_undo_redo_controller);
    return 0;
}