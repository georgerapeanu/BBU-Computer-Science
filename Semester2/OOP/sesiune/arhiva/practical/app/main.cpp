#include <QApplication>
#include <QPushButton>
#include "User.h"
#include "Question.h"
#include "Answer.h"
#include "FileRepository.h"
#include "Controller.h"
#include "GUIManager.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    FileRepository<User> users("users.txt");
    FileRepository<Question> questions("questions.txt");
    FileRepository<Answer> answers("answers.txt");
    Controller controller(users, questions, answers);
    GUIManager gui(controller);

    return QApplication::exec();
}
