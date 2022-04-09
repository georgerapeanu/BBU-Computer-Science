//
// Created by georgerapeanu on 07.04.2022.
//

#include "AppTests.h"
#include "SchoolController.h"

#include <cassert>
#include "AppException.h"
using namespace std;

void AppTests::test_remove() {
    SchoolController controller;

    controller.add_school("Avram_Iancu", 46.77, 23.60, "15.06.2022", true);
    controller.add_school("George_Cosbuc", 46.77, 23.58, "18.04.2022", false);
    controller.add_school("Alexandru_Vaida_Voievod", 46.77, 23.63, "23.04.2022", false);
    controller.add_school("Romulus_Guga", 46.53, 24.57, "04.05.2022", false);
    controller.add_school("Colegiul_Transilvania", 46.54, 24.57, "03.05.2022", false);


    controller.remove_school("Romulus_Guga", 46.53, 24.57);
    try{
        controller.remove_school("Romulus_Guga", 46.53, 24.57);
        assert(false);
    }catch(AppException ex){
        ;
    }

    vector<School> schools;
    schools.push_back(School("Alexandru_Vaida_Voievod", 46.77, 23.63, "23.04.2022", false));
    schools.push_back(School("Avram_Iancu", 46.77, 23.60, "15.06.2022", true));
    schools.push_back(School("Colegiul_Transilvania", 46.54, 24.57, "03.05.2022", false));
    schools.push_back(School("George_Cosbuc", 46.77, 23.58, "18.04.2022", false));

    vector<School> controller_schools = controller.get_all_schools_sorted_by_name();
    assert(schools.size() == controller_schools.size());

    for(int i = 0;i < (int)schools.size();i++){
        assert(controller_schools[i].get_name() == schools[i].get_name());
    }

}

void AppTests::test_mark() {
    SchoolController controller;

    controller.add_school("Avram_Iancu", 46.77, 23.60, "15.06.2022", true);
    controller.add_school("George_Cosbuc", 46.77, 23.58, "18.04.2022", false);
    controller.add_school("Alexandru_Vaida_Voievod", 46.77, 23.63, "23.04.2022", false);
    controller.add_school("Romulus_Guga", 46.53, 24.57, "04.05.2022", false);
    controller.add_school("Colegiul_Transilvania", 46.54, 24.57, "03.05.2022", false);


    controller.mark_all_schools_as_visited_before_date("5.05.2022");

    vector<School> schools;
    schools.push_back(School("Alexandru_Vaida_Voievod", 46.77, 23.63, "23.04.2022", false));
    schools.push_back(School("Avram_Iancu", 46.77, 23.60, "15.06.2022", true));
    schools.push_back(School("Colegiul_Transilvania", 46.54, 24.57, "03.05.2022", false));
    schools.push_back(School("George_Cosbuc", 46.77, 23.58, "18.04.2022", false));
    schools.push_back(School("Romulus_Guga", 46.53, 24.57, "04.05.2022", false));

    vector<School> controller_schools = controller.get_all_schools_sorted_by_name();
    assert(schools.size() == controller_schools.size());

    for(int i = 0;i < (int)schools.size();i++){
        assert(controller_schools[i].get_name() == schools[i].get_name());
    }
}
