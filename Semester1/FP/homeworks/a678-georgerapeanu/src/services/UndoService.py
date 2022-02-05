from src.repository.UndoRepository import UndoRepository
from src.services.ServiceExceptions import UndoServiceException


class UndoService:
    def __init__(self, undo_repository):
        """ Constructor for UndoService

        :param undo_repository: the undo repository
        :type undo_repository: GeneralRepository
        """
        self.__undo_repository = undo_repository

    def undo(self):
        self.__undo_repository.undo()

    def redo(self):
        self.__undo_repository.redo()

    def clear(self):
        self.__undo_repository.clear()
