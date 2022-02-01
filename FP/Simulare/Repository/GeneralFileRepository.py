from Domain.Exceptions import GeneralFileRepositoryException
from Domain.IdObject import IdObject


class GeneralFileRepository:
    """This implements a general repository that uses files
    """
    def __init__(self, cls, filename):
        """ Constructor for the general repository
            It needs the class that it is going to store and the filename where it is going to store it

        :param cls: class
        :type: class
        :param filename: the filename where it needs to store it
        :type filename: str
        """

        if type(filename) != str or len(filename) == 0:
            raise GeneralFileRepositoryException("invalid filename")

        self.__entities = {}
        self.__cls = cls
        self.__filename = filename

    def save(self):
        """ Saves on disk from memory.

        :return: None
        """
        with open(self.__filename, "w") as f:
            for entity in self.__entities.values():
                f.write(str(entity) + "\n")

    def load(self):
        """ Loads from disk to memory.

        :return: None
        """

        self.__entities = {}
        with open(self.__filename, "r") as f:
            for line in f:
                if len(line) == 0:
                    continue
                entity = self.__cls.init_from_string(line)
                if entity.id in self.__entities:
                    raise GeneralFileRepositoryException("File is invalid")
                self.__entities[entity.id] = entity

    def add(self, entity):
        """ Adds an entity to the repository. If entity id already exists, raises GeneralFileRepositoryException

        :param entity: entity
        :type entity: IdObject
        :return:
        """

        if entity.id in self.__entities:
            raise GeneralFileRepositoryException("Entity id already exists")

        self.__entities[entity.id] = entity

    def update(self, entity):
        """ Adds an entity to the repository. If entity id already exists, raises GeneralFileRepositoryException

        :param entity: entity
        :type entity: IdObject
        :return:
        """

        if entity.id not in self.__entities:
            raise GeneralFileRepositoryException("Entity id does not exist")

        self.__entities[entity.id] = entity

    def get_by_id(self, id):
        """ Gets entity by id

        :param id: the id of the entity
        :type id: int
        :return: entity
        """

        if id not in self.__entities:
            raise GeneralFileRepositoryException("Entity id does not exist")

        return self.__entities[id]

    def delete_by_id(self, id):
        """ Deletes entity from repository by given id

        :param id: id
        :type id: int
        :return: None
        """

        if id not in self.__entities:
            raise GeneralFileRepositoryException("Entity id does not exist")

        del self.__entities[id]

    def get_all(self):
        """ Gets all entities

        :return: list
        """

        return list(self.__entities.values())

