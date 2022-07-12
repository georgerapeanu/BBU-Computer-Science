import os.path
import pickle

from src.repository.GeneralRepository import GeneralRepository


class BinaryRepository(GeneralRepository):
    def __init__(self, entity_class, filename):
        super().__init__(entity_class)
        self.__filename = filename
        if not os.path.exists(filename):
            self.save()

    def save(self):
        f = open(self.__filename, "wb")
        pickle.dump(self._entities, f)
        f.close()

    def load(self):
        f = open(self.__filename, "rb")
        self._entities = pickle.load(f)
        f.close()
