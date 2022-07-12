//
// Created by georgerapeanu on 12.06.2022.
//

#include "AbstractSubject.h"
#include <algorithm>

void AbstractSubject::notify() {
    for(auto it:this->observers){
        it->update();
    }
}

void AbstractSubject::attachObserver(AbstractObserver *observer) {
    this->observers.push_back(observer);
}

void AbstractSubject::detachObserver(AbstractObserver *observer) {
    this->observers.erase(std::find(this->observers.begin(), this->observers.end(), observer));
}
