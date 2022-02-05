from src.domain.ActionComposite import ActionComposite
from src.domain.ActionLeaf import ActionLeaf


class UndoAction:
    def __init__(self, undo_action, redo_action):
        """Constructor for UndoAction

        :param undo_action: undo action
        :type undo_action: ActionLeaf|ActionComposite
        :param redo_action: redo action
        :type redo_action: ActionLeaf|ActionComposite
        """
        self.__undo_action = undo_action
        self.__redo_action = redo_action

    def undo(self):
        self.__undo_action.do_action()

    def redo(self):
        self.__redo_action.do_action()
