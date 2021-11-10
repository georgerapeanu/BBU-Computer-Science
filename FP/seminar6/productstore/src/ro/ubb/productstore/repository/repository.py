"""
@author: radu


"""
from ro.ubb.productstore.domain.validators import ProductStoreException


class RepositoryException(ProductStoreException):
    pass


class Repository(object):
    def __init__(self, validator_class):
        self.__validator_class = validator_class
        self.__entities = {}

    def find_by_id(self, entity_id):
        if entity_id in self.__entities:
            return self.__entities[entity_id]
        return None

    def save(self, entity):
        if self.find_by_id(entity.id) is not None:
            raise RepositoryException("duplicate id {0}.".format(entity.id))
        self.__validator_class.validate(entity)
        self.__entities[entity.id] = entity

    def update(self, entity_id, entity):
        pass

    def delete_by_id(self, entity_id):
        pass

    def get_all(self):
        return list(self.__entities.values())
