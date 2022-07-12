//
// Created by georgerapeanu on 09.06.2022.
//

#ifndef PRACTIC_ABSTRACTSUBJECT_H
#define PRACTIC_ABSTRACTSUBJECT_H

#include "AbstractObserver.h"
#include <vector>

class AbstractSubject{
    std::vector<AbstractObserver*> observers;
public:
    virtual void attachObserver(AbstractObserver* observer);
    virtual void detachObserver(AbstractObserver* observer);
    virtual void notify();
};

#endif //PRACTIC_ABSTRACTSUBJECT_H
