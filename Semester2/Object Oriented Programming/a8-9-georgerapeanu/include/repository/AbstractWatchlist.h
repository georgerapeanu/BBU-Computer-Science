/*!
 * @file AbstractWatchlist.h this file contains the model for an abstract watchlist
 */

//
// Created by georgerapeanu on 18.04.2022.
//

#ifndef A8_9_GEORGERAPEANU_ABSTRACTWATCHLIST_H
#define A8_9_GEORGERAPEANU_ABSTRACTWATCHLIST_H
#pragma once
#include "AbstractRepository.h"


//! this struct contains the model for an AbstractWatchlist
template<class T>
class AbstractWatchlist:public AbstractRepository<T>{
public:
    //! This method should save to a file
    virtual void save()const = 0;
    //! This method display the file
    virtual void display()const = 0;
};

#endif //A8_9_GEORGERAPEANU_ABSTRACTWATCHLIST_H
