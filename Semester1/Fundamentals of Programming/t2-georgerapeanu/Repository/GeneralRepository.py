from Repository.RepositoryExceptions import GeneralRepositoryException


class GeneralRepository:
    """ This is a repository that is as abstract as much as possible.

    """
    def __init__(self):
        self._entities = {}

    def add(self, entity):
        """ This method adds the entity to the repository. Throws GeneralRepositoryException
        if id is already taken or invalid

        :param entity: the entity to be added
        :return: None
        """

        if entity.id in self._entities:
            raise GeneralRepositoryException("entity id already taken")

        self._entities[entity.id] = entity

    def update(self, entity_id, entity):
        """ This method updates the entity specified by entity_id
            If entity_id doesnt exist raises GeneralRepositoryException
            If entity id does not correspond to specified id raises GeneralRepositoryException

        :param entity_id: the entity's id to be updated
        :param entity: the entity with which to update
        :return: None
        """

        if entity_id != entity.id:
            raise GeneralRepositoryException("entity id does not correspond")

        if entity_id not in self._entities:
            raise GeneralRepositoryException("entity id doesn't exist")

        self._entities[entity_id] = entity

    def delete(self, entity_id):
        """ This method deletes the entity specified by entity_id from the repository
            If entity_id doesnt exist raises GeneralRepositoryException

        :param entity_id: the entity's id to be deleted
        :type entity_id: int
        :return: None
        """

        if entity_id not in self._entities:
            raise GeneralRepositoryException("entity id doesn't exist")

        del self._entities[entity_id]

    def list(self):
        """ This method returns a list containing all the entities

        :return: None
        """
        entities = [x for x in self._entities.values()]

        return entities

    def get_by_id(self, id):
        """ This method returns the entity with the given id or None if it doesn't exist

        :param id: the id of the entity
        :type id: int
        :return: entity or None if it doesnt exist
        """

        if id in self._entities:
            return self._entities[id]

        return None

    def __len__(self):
        """ This method returns the number of elements stored by the repository
            It overwrites len

        :return: int representing the number of entities
        """
        return len(self._entities)
