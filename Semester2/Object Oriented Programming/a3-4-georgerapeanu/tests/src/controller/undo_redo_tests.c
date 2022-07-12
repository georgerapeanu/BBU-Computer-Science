#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../../include/controller/undo_redo_tests.h"
#include "../../../include/repository/repository.h"
#include "../../../include/domain/country.h"
#include "../../../include/repository/undo_redo_repository.h"
#include "../../../include/controller/country_controller.h"
#include "../../../include/controller/undo_redo_controller.h"

void undo_redo_test1(){
    int tmp_error = 0;
    repository_t* p_repository = create_repository(sizeof(country_t),&delete_country_data,NULL);
    undo_redo_repository_t* p_undo_redo_repository = create_undo_redo_repository(NULL);
    country_controller_t* p_controller = create_country_controller(p_repository, p_undo_redo_repository, NULL);
    undo_redo_controller_t* p_undo_redo_controller = create_undo_redo_controller(p_undo_redo_repository, NULL);

    country_t* p_countries[100]; /// for test uses

    add_country_ui(p_controller,"c1", "invalid", 10, 1, NULL);
    add_country_ui(p_controller,"c1", "america", 10, 1, NULL);
    add_country_ui(p_controller,"c1", "invalid", 10, 1, NULL);
    add_country_ui(p_controller,"c2", "invalid", 10, 1, NULL);
    add_country_ui(p_controller, "c2", "africa", 200, 1, NULL);

    assert(p_repository->p_elements->size == 2);
    p_countries[0] = (country_t*)get_position_repository(p_repository, 0, NULL);
    p_countries[1] = (country_t*)get_position_repository(p_repository, 1, NULL);
    assert(strcmp(p_countries[0]->name, "c1") == 0);
    assert(strcmp(p_countries[0]->continent, "america") == 0);
    assert(p_countries[0]->population == 10);
    assert(strcmp(p_countries[1]->name, "c2") == 0);
    assert(strcmp(p_countries[1]->continent, "africa") == 0);
    assert(p_countries[1]->population == 200);

    undo(p_undo_redo_controller, NULL);
    assert(p_repository->p_elements->size == 1);
    p_countries[0] = (country_t*)get_position_repository(p_repository, 0, NULL);
    assert(strcmp(p_countries[0]->name, "c1") == 0);
    assert(strcmp(p_countries[0]->continent, "america") == 0);
    assert(p_countries[0]->population == 10);
    redo(p_undo_redo_controller, NULL);

    assert(p_repository->p_elements->size == 2);
    p_countries[0] = (country_t*)get_position_repository(p_repository, 0, NULL);
    p_countries[1] = (country_t*)get_position_repository(p_repository, 1, NULL);
    assert(strcmp(p_countries[0]->name, "c1") == 0);
    assert(strcmp(p_countries[0]->continent, "america") == 0);
    assert(p_countries[0]->population == 10);
    assert(strcmp(p_countries[1]->name, "c2") == 0);
    assert(strcmp(p_countries[1]->continent, "africa") == 0);
    assert(p_countries[1]->population == 200);
    undo(p_undo_redo_controller, NULL);

    remove_country_ui(p_controller, "c2", 1, &tmp_error);
    assert(tmp_error == 11);
    tmp_error = 0;
    remove_country_ui(p_controller, "c1", 1, &tmp_error);
    redo(p_undo_redo_controller, &tmp_error);
    assert(tmp_error == 20);
    tmp_error = 0;

    assert(p_repository->p_elements->size == 0);
    undo(p_undo_redo_controller, NULL);
    add_country_ui(p_controller, "c3", "europe", 100, 1, NULL);
    migrate_ui(p_controller, "c3", "c2", 10, 1, &tmp_error);
    assert(tmp_error == 11);
    migrate_ui(p_controller, "c3", "c1", 10, 1, &tmp_error);
    assert(p_repository->p_elements->size == 2);
    p_countries[0] = (country_t*)get_position_repository(p_repository, 0, NULL);
    p_countries[1] = (country_t*)get_position_repository(p_repository, 1, NULL);
    assert(strcmp(p_countries[0]->name, "c1") == 0);
    assert(strcmp(p_countries[0]->continent, "america") == 0);
    assert(p_countries[0]->population == 20);
    assert(strcmp(p_countries[1]->name, "c3") == 0);
    assert(strcmp(p_countries[1]->continent, "europe") == 0);
    assert(p_countries[1]->population == 90);

    remove_country_ui(p_controller, "c1", 1, NULL);

    update_country_ui(p_controller, "c1", 100, 1, &tmp_error);
    assert(tmp_error == 11);
    tmp_error = 0;
    update_country_ui(p_controller, "c3", 100, 1, &tmp_error);
    assert(p_repository->p_elements->size == 1);
    p_countries[0] = (country_t*)get_position_repository(p_repository, 0, NULL);
    assert(strcmp(p_countries[0]->name, "c3") == 0);
    assert(strcmp(p_countries[0]->continent, "europe") == 0);
    assert(p_countries[0]->population == 100);
    add_country_ui(p_controller, "c4", "australia", 1300, 1, NULL);
    migrate_ui(p_controller, "c4", "c3", 200, 1, NULL);
    assert(p_repository->p_elements->size == 2);
    p_countries[0] = (country_t*)get_position_repository(p_repository, 0, NULL);
    p_countries[1] = (country_t*)get_position_repository(p_repository, 1, NULL);
    assert(strcmp(p_countries[0]->name, "c3") == 0);
    assert(strcmp(p_countries[0]->continent, "europe") == 0);
    assert(p_countries[0]->population == 300);
    assert(strcmp(p_countries[1]->name, "c4") == 0);
    assert(strcmp(p_countries[1]->continent, "australia") == 0);
    assert(p_countries[1]->population == 1100);

    /* Right now the active operations are:
     * add_country_ui(p_controller,"c1", "america", 10, 1, NULL); -> (c1, america, 10)
     * add_country_ui(p_controller, "c3", "europe", 100, 1, NULL); -> (c1, america, 10), (c3, europe, 100)
     * migrate_ui(p_controller, "c3", "c1", 10, 1, &tmp_error); -> (c1, america, 20), (c3, europe, 90)
     * remove_country_ui(p_controller, "c1", 1, NULL); -> (c3, europe, 90)
     * update_country_ui(p_controller, "c3", 100, 1, &tmp_error); -> (c3, europe, 100)
     * add_country_ui(p_controller, "c4", "australia", 1300, 1, NULL); -> (c3, europe, 100), (c4, australia, 1300)
     * migrate_ui(p_controller, "c4", "c3", 200, 1, NULL); -> (c3, europe ,300), (c4, australia, 1100)
     */

    undo(p_undo_redo_controller, NULL);
    assert(p_repository->p_elements->size == 2);
    p_countries[0] = (country_t*)get_position_repository(p_repository, 0, NULL);
    p_countries[1] = (country_t*)get_position_repository(p_repository, 1, NULL);
    assert(strcmp(p_countries[0]->name, "c3") == 0);
    assert(strcmp(p_countries[0]->continent, "europe") == 0);
    assert(p_countries[0]->population == 100);
    assert(strcmp(p_countries[1]->name, "c4") == 0);
    assert(strcmp(p_countries[1]->continent, "australia") == 0);
    assert(p_countries[1]->population == 1300);

    undo(p_undo_redo_controller, NULL);
    assert(p_repository->p_elements->size == 1);
    p_countries[0] = (country_t*)get_position_repository(p_repository, 0, NULL);
    assert(strcmp(p_countries[0]->name, "c3") == 0);
    assert(strcmp(p_countries[0]->continent, "europe") == 0);
    assert(p_countries[0]->population == 100);

    undo(p_undo_redo_controller, NULL);
    assert(p_repository->p_elements->size == 1);
    p_countries[0] = (country_t*)get_position_repository(p_repository, 0, NULL);
    assert(strcmp(p_countries[0]->name, "c3") == 0);
    assert(strcmp(p_countries[0]->continent, "europe") == 0);
    assert(p_countries[0]->population == 90);

    undo(p_undo_redo_controller, NULL);
    assert(p_repository->p_elements->size == 2);
    p_countries[0] = (country_t*)get_position_repository(p_repository, 0, NULL);
    p_countries[1] = (country_t*)get_position_repository(p_repository, 1, NULL);
    assert(strcmp(p_countries[0]->name, "c3") == 0);
    assert(strcmp(p_countries[0]->continent, "europe") == 0);
    assert(p_countries[0]->population == 90);
    assert(strcmp(p_countries[1]->name, "c1") == 0);
    assert(strcmp(p_countries[1]->continent, "america") == 0);
    assert(p_countries[1]->population == 20);

    undo(p_undo_redo_controller, NULL);
    assert(p_repository->p_elements->size == 2);
    p_countries[0] = (country_t*)get_position_repository(p_repository, 0, NULL);
    p_countries[1] = (country_t*)get_position_repository(p_repository, 1, NULL);
    assert(strcmp(p_countries[0]->name, "c3") == 0);
    assert(strcmp(p_countries[0]->continent, "europe") == 0);
    assert(p_countries[0]->population == 100);
    assert(strcmp(p_countries[1]->name, "c1") == 0);
    assert(strcmp(p_countries[1]->continent, "america") == 0);
    assert(p_countries[1]->population == 10);

    undo(p_undo_redo_controller, NULL);
    assert(p_repository->p_elements->size == 1);
    p_countries[0] = (country_t*)get_position_repository(p_repository, 0, NULL);
    assert(strcmp(p_countries[0]->name, "c1") == 0);
    assert(strcmp(p_countries[0]->continent, "america") == 0);
    assert(p_countries[0]->population == 10);

    undo(p_undo_redo_controller, NULL);
    assert(p_repository->p_elements->size == 0);

    undo(p_undo_redo_controller, &tmp_error);
    assert(tmp_error == 19);
    tmp_error = 0;

    delete_undo_redo_controller(p_undo_redo_controller);
    delete_country_controller(p_controller);
    delete_repository(p_repository);
    delete_undo_redo_repository(p_undo_redo_repository);
}

void undo_redo_test_all(){
    undo_redo_test1();
}