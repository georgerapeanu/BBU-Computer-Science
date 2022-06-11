//
// Created by georgerapeanu on 11.06.2022.
//

#include "GUIManager.h"

GUIManager::GUIManager(Controller &controller) {
    for(auto &it:controller.getAllUsers()){
        UserMainWindow* user_main_window = new UserMainWindow(it, controller);
        controller.attachObserver(user_main_window);
        user_main_window->show();
    }
    UserSearchWindow* user_search_window = new UserSearchWindow(controller);
    controller.attachObserver(user_search_window);
    user_search_window->show();
}
