//
// Created by georgerapeanu on 09.06.2022.
//

#include <algorithm>
#include "AbstractSubject.h"

void AbstractSubject::attachObserver(AbstractObserver *observer) {
    this->observers.push_back(observer);
}

void AbstractSubject::detachObserver(AbstractObserver *observer) {
    this->observers.erase(std::find(this->observers.begin(), this->observers.end(), observer));
}

void AbstractSubject::notify() {
    for(auto it:this->observers){
        it->update();
    }
}

