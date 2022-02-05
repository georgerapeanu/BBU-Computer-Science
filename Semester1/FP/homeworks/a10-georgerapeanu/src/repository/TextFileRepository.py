import os.path
from src.repository.GeneralRepository import GeneralRepository
from src.repository.RepositoryExceptions import TextFileRepositoryException
from src.utils.CustomIterable import CustomIterable


class TextFileRepository(GeneralRepository):
    def __init__(self, entity_class, filename):
        super().__init__(entity_class)
        self.__filename = filename
        if not os.path.exists(filename):
            self.save()

    def save(self):
        f = open(self.__filename, "w")
        for entity in self._entities:
            f.write(self._entity_class.to_file_string(entity) + "\n")
        f.close()

    def load(self):
        self._entities = CustomIterable()
        f = open(self.__filename, "r")
        for line in f.readlines():
            entity = self._entity_class.from_file_string(line.strip())
            if entity.id in self._entities:
                f.close()
                raise TextFileRepositoryException("corrupt file")
            self._entities[entity.id] = entity
        f.close()
