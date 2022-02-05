import os.path
from src.repository.GeneralRepository import GeneralRepository
from src.repository.RepositoryExceptions import TextFileRepositoryException


class TextFileRepository(GeneralRepository):
    def __init__(self, entity_class, filename):
        super().__init__(entity_class)
        self.__filename = filename
        if not os.path.exists(filename):
            self.save()

    def save(self):
        f = open(self.__filename, "w")
        for entity_id in self._entities:
            f.write(self._entity_class.to_file_string(self._entities[entity_id]) + "\n")
        f.close()

    def load(self):
        self._entities = {}
        f = open(self.__filename, "r")
        for line in f.readlines():
            entity = self._entity_class.from_file_string(line.strip())
            if entity.id in self._entities:
                f.close()
                raise TextFileRepositoryException("corrupt file")
            self._entities[entity.id] = entity
        f.close()
