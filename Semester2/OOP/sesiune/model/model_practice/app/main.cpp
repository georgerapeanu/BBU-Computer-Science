#include <QApplication>
#include <QPushButton>
#include "MainGUI.h"
#include "IssueController.h"
#include "UserController.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GeneralFileRepository<User> users("users.txt");
    GeneralFileRepository<Issue> issues("issues.txt");
    IssueController issue_controller(issues);
    UserController user_controller(users);
    MainGUI gui(issue_controller, user_controller);
    //gui.show();
    return QApplication::exec();
}
