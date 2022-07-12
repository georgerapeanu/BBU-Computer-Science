//
// Created by georgerapeanu on 26.05.2022.
//

#ifndef T3_GEORGERAPEANU_GUI_H
#define T3_GEORGERAPEANU_GUI_H

#include <QtWidgets>
#include "Controller.h"

class GUI : public QWidget {
    Q_OBJECT
    QLabel* list_label;
    QListWidget* list;
    QLineEdit* searchBar;
    QLineEdit* similarity;
    Controller& controller;

public:

    GUI(Controller& controller, QWidget* parrent = Q_NULLPTR);

public slots:
    void show_documents();
    void handle_item_change(int row);
};


#endif //T3_GEORGERAPEANU_GUI_H
