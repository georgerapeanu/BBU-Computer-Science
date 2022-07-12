//
// Created by georgerapeanu on 26.05.2022.
//

#include <QtWidgets/QApplication>
#include <QtWidgets>
#include "GUI.h"
#include "FileRepository.h"
#include "Controller.h"
#include "Exceptions.h"
#include <iostream>

int main(int argc, char** argv) {

    QApplication app(argc, argv);
    try{
        FileRepository* repository = new FileRepository("Documents.txt");
        Controller* controller = new Controller(*repository);
        GUI* gui = new GUI(*controller);

        gui->show();
    }catch(AppException &exception){
        std::cout << "Error: " + exception.get_message() << std::endl;
        return 1;
    }
    return app.exec();
}