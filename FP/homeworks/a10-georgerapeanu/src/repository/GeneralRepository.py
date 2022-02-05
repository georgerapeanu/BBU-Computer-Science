from src.repository.RepositoryExceptions import GeneralRepositoryException
from src.utils.CustomIterable import CustomIterable


class GeneralRepository:
    """ This is a repository that is as abstract as much as possible.
        It also adapts to the problem, so it assume that entities have an id and name property

    """
    def __init__(self, entity_class):
        self._entities = CustomIterable()
        self._entity_class = entity_class

    def load(self):
        """Loads data into memory. Not used here, but is required for polymorphism

        :return: None
        """
        pass

    def save(self):
        """Save data from memory. Not used here, but required for polymorphism

        :return: None
        """
        pass

    def add(self, entity):
        """ This method adds the entity to the repository. Throws GeneralRepositoryException
        if id is already taken or invalid

        :param entity: the entity to be added
        :return: None
        """

        self.load()
        if entity.id in self._entities:
            raise GeneralRepositoryException("entity id already taken")

        self._entities[entity.id] = entity
        self.save()

    def update(self, entity_id, entity):
        """ This method updates the entity specified by entity_id
            If entity_id doesnt exist raises GeneralRepositoryException
            If entity id does not correspond to specified id raises GeneralRepositoryException

        :param entity_id: the entity's id to be updated
        :param entity: the entity with which to update
        :return: None
        """

        self.load()
        if entity_id != entity.id:
            raise GeneralRepositoryException("entity id does not correspond")

        if entity_id not in self._entities:
            raise GeneralRepositoryException("entity id doesn't exist")

        self._entities[entity_id] = entity
        self.save()

    def delete(self, entity_id):
        """ This method deletes the entity specified by entity_id from the repository
            If entity_id doesnt exist raises GeneralRepositoryException

        :param entity_id: the entity's id to be deleted
        :type entity_id: int
        :return: None
        """

        self.load()
        if entity_id not in self._entities:
            raise GeneralRepositoryException("entity id doesn't exist")

        del self._entities[entity_id]
        self.save()

    def list(self):
        """ This method returns a list containing all the entities

        :return: None
        """
        self.load()
        entities = [x for x in self._entities]

        return entities

    def get_by_id(self, id):
        """ This method returns the entity with the given id or None if it doesn't exist

        :param id: the id of the entity
        :type id: int
        :return: entity or None if it doesnt exist
        """
        self.load()

        if id in self._entities:
            return self._entities[id]

        return None

    def __len__(self):
        return len(self._entities)
