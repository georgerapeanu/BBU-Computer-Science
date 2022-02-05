from src.domain.ActionLeaf import ActionLeaf
from src.domain.UndoAction import UndoAction
from src.services.ServiceExceptions import DisciplinesServiceException
from src.domain.Discipline import Discipline
from src.repository.GeneralRepository import GeneralRepository
from src.repository.UndoRepository import UndoRepository


class DisciplinesService:
    def __init__(self, discipline_repository, undo_repository):
        """ Constructor for DisciplinesService

        :param discipline_repository: discipline repository
        :type discipline_repository: GeneralRepository
        :param undo_repository: undo repository
        :type undo_repository: UndoRepository
        """
        self.__repository = discipline_repository
        self.__undo_repository = undo_repository

    def add_discipline(self, id, name):
        """ This method adds the discipline with the specified id and name

        :param id: id of discipline
        :type id: int
        :param name: name of discipline
        :type name: string
        :return: None
        """
        discipline = Discipline(id, name)
        self.__repository.add(discipline)
        undo_action = ActionLeaf(self.__repository.delete, tuple([discipline.id]))
        redo_action = ActionLeaf(self.__repository.add, tuple([discipline]))
        action = UndoAction(undo_action, redo_action)
        self.__undo_repository.add(action)

    def update_discipline(self, id, name):
        """ This method updates the discipline with the specified id

        :param id: id of discipline
        :type id: int
        :param name: name of discipline
        :type name: string
        :return: None
        """

        discipline = self.__repository.get_by_id(id)
        if discipline is None:
            raise DisciplinesServiceException("cannot update discipline with specified id")
        self.__repository.update(id, Discipline(id, name))
        undo_action = ActionLeaf(self.__repository.update, tuple([id, discipline]))
        redo_action = ActionLeaf(self.__repository.update, tuple([id, Discipline(id, name)]))
        action = UndoAction(undo_action, redo_action)
        self.__undo_repository.add(action)

    def get_by_id(self, id):
        """ This method returns a discipline with specified id or None if it doesn't exist

        :param id: the specified id
        :type id: int
        :return: discipline or None if it doesn't exist
        """
        return self.__repository.get_by_id(id)

    def list_by_name(self, name):
        """ This method returns a list of all disciplines that match given name

        :param name: the given name
        :type name: string
        :return: list of disciplines
        """
        return list(filter(lambda x: x.name.lower().find(name.lower()) != -1, self.__repository.list()))

    def list(self):
        """ This method returns a list of all disciplines

        :return: list of disciplines
        """
        return self.__repository.list()
