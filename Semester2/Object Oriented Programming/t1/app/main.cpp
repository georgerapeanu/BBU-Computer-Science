//
// Created by georgerapeanu on 07.04.2022.
//

#include "UI.h"
#include "SchoolController.h"
#include "SchoolRepository.h"

using namespace std;

int main(){
    SchoolController controller;
    UI ui(&controller);

    controller.add_school("Avram_Iancu", 46.77, 23.60, "15.06.2022", true);
    controller.add_school("George_Cosbuc", 46.77, 23.58, "18.04.2022", false);
    controller.add_school("Alexandru_Vaida_Voievod", 46.77, 23.63, "23.04.2022", false);
    controller.add_school("Romulus_Guga", 46.53, 24.57, "04.05.2022", false);
    controller.add_school("Colegiul_Transilvania", 46.54, 24.57, "03.05.2022", false);

    ui.run_ui();

    return 0;
}