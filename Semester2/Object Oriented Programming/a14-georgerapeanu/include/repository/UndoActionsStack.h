//
// Created by georgerapeanu on 23.05.2022.
//

#ifndef A14_GEORGERAPEANU_UNDOACTIONSSTACK_H
#define A14_GEORGERAPEANU_UNDOACTIONSSTACK_H

#include <vector>
#include "AbstractMovieAction.h"
#include "Exceptions.h"

class UndoActionsStack{
    int current_action;
    std::vector<AbstractMovieAction*> actions;
public:
    UndoActionsStack();
    ~UndoActionsStack();

    /*!
     * This method pushes an action to the top of the stack
     * @param action a pointer to the action
     */
    void push_back(AbstractMovieAction* action);

    /*!
     * This method undoes the current action
     * @raises UndoException if no undo is possible
     */
    void undo();
    /*!
     * This method redoes the current action
     * @raises UndoException if no redo is possible
     */
    void redo();
};


#endif //A14_GEORGERAPEANU_UNDOACTIONSSTACK_H
