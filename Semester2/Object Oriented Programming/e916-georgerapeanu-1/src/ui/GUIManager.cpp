//
// Created by georgerapeanu on 12.06.2022.
//

#include "GUIManager.h"

#include <vector>
#include "User.h"
#include "UserMainWindow.h"
#include "SearchWindow.h"

GUIManager::GUIManager(Controller &controller) {
    std::vector<User> users = controller.getAllUsers();

    for(const auto &user : users){
        UserMainWindow* user_window = new UserMainWindow(controller, user);
        controller.attachObserver(user_window);
        user_window->show();
    }

    SearchWindow* search_window = new SearchWindow(controller);
    controller.attachObserver(search_window);
    search_window->show();
}

