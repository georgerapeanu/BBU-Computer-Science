from src.Domain.Exceptions import GenericFileRepositoryException
import os


class GenericFileRepository:
    """ This is the model for a general file repository that holds any IdObjects

    """
    def __init__(self, cls, file):
        """ Constructor for GenericFileRepository

            :param cls: the class that it holds(should implement str and init_from_str
            :type cls: Class
            :param file: the file name with which it persists
            :type file: string
        """
        self.__entities = {}
        self.__file = file
        self.__cls = cls
        if not os.path.exists(file):
            self.__save()

    def __save(self):
        """ Saves to file the contents from memory. Clears memory

        :return: None
        """

        with open(self.__file, "w") as f:
            for elem in self.__entities.values():
                f.write(str(elem) + "\n")
        self.__entities = {}

    def __load(self):
        """ Loads from file the contents into memory.

        :return: None
        """

        self.__entities = {}
        with open(self.__file, "r") as f:
            for line in f:
                entity = self.__cls.init_from_string(line)
                self.__entities[entity.id] = entity

    def add(self, entity):
        """ Adds the entity to the repository. Raises GenericFileRepositoryException if entity id is taken

        :param entity: the entity to be added
        :type entity: IdObject
        :return: None
        """

        self.__load()

        if entity.id in self.__entities:
            raise GenericFileRepositoryException("Flight id is not unique")
        self.__entities[entity.id] = entity
        self.__save()

    def delete(self, id):
        """ Deletes the entity with specified id. Raises GenericFileRepositoryException if it doesnt exist

        :param id: the entity id to be deleted
        :type id: int|str
        :return: None
        """

        self.__load()

        if id not in self.__entities:
            raise GenericFileRepositoryException("Flight id does not exist")
        del self.__entities[id]
        self.__save()

    def get_by_id(self, id):
        """ Gets an entity by its id

        :param id: the id
        :type id: int|str
        :return: entity of self.__cls
        """
        self.__load()

        if id not in self.__entities:
            raise GenericFileRepositoryException("Flight id does not exist")
        return self.__entities[id]

    def get_all(self):
        """ Gets all entities in a list

        :return: list
        """
        ans = []
        self.__load()
        for elem in self.__entities.values():
            ans.append(elem)
        return ans
