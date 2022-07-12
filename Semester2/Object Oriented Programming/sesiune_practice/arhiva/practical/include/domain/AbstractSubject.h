//
// Created by georgerapeanu on 11.06.2022.
//

#ifndef PRACTICAL_ABSTRACTSUBJECT_H
#define PRACTICAL_ABSTRACTSUBJECT_H

#include "AbstractObserver.h"
#include <vector>


class AbstractSubject{
    std::vector<AbstractObserver*> observers;
public:

    void attachObserver(AbstractObserver* observer);
    void detachObserver(AbstractObserver* observer);
    void notify();
};

#endif //PRACTICAL_ABSTRACTSUBJECT_H
