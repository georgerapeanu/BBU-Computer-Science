#include <QApplication>
#include <QPushButton>

#include "User.h"
#include "Answer.h"
#include "Question.h"
#include "GenericFileRepository.h"
#include "Controller.h"
#include "GUIManager.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    GenericFileRepository<User> users("users.txt");
    GenericFileRepository<Question> questions("questions.txt");
    GenericFileRepository<Answer> answers("answers.txt");

    Controller controller(users, questions, answers);
    GUIManager gui(controller);

    return QApplication::exec();
}
