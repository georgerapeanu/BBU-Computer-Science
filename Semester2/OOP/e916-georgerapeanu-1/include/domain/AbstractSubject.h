//
// Created by georgerapeanu on 12.06.2022.
//

#ifndef E916_GEORGERAPEANU_1_ABSTRACTSUBJECT_H
#define E916_GEORGERAPEANU_1_ABSTRACTSUBJECT_H

#include "AbstractObserver.h"

#include <vector>

class AbstractSubject{
    std::vector<AbstractObserver*> observers;
public:
    void notify();
    void attachObserver(AbstractObserver* observer);
    void detachObserver(AbstractObserver* observer);
};

#endif //E916_GEORGERAPEANU_1_ABSTRACTSUBJECT_H
