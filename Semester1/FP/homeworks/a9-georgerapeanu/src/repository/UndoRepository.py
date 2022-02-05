from src.domain.UndoAction import UndoAction
from src.repository.RepositoryExceptions import UndoRepositoryException


class UndoRepository:
    """This class handles the UndoRepository
        This is required because if someone issues an add after undo then we must lose any operations after that

    """
    def __init__(self):
        self.actions = []
        self.index = -1

    def add(self, undo_action):
        """Adds to the repository

        :param undo_action: undo_action
        :type undo_action: UndoAction
        :return: None
        """
        while len(self.actions) > self.index + 1:
            self.actions.pop()

        self.actions.append(undo_action)
        self.index += 1

    def undo(self):
        if self.index == -1:
            raise UndoRepositoryException("Cannot undo any further")
        self.actions[self.index].undo()
        self.index -= 1

    def redo(self):
        if self.index + 1 >= len(self.actions):
            raise UndoRepositoryException("Cannot redo any further")
        self.index += 1
        self.actions[self.index].redo()

    def clear(self):
        self.actions = []
        self.index = -1
