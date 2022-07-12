//
// Created by georgerapeanu on 23.05.2022.
//

#include "UndoActionsStack.h"


UndoActionsStack::UndoActionsStack() {
    this->actions = std::vector<AbstractMovieAction*>();
    this->current_action = -1;
}

void UndoActionsStack::push_back(AbstractMovieAction *action) {
    while((int)this->actions.size() > this->current_action + 1){
        delete this->actions.back();
        this->actions.pop_back();
    }
    this->actions.push_back(action);
    this->current_action++;
}

void UndoActionsStack::undo() {
    if(this->current_action <= -1){
        throw UndoException("No further undo possible");
    }
    this->actions[this->current_action--]->undo();
}

void UndoActionsStack::redo() {
    if(this->current_action >= (int)this->actions.size() - 1){
        throw UndoException("No further redo possible");
    }
    this->actions[++this->current_action]->redo();
}

UndoActionsStack::~UndoActionsStack() {
    for(auto it:this->actions){
        delete it;
    }
}
