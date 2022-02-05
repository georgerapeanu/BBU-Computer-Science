class CustomIterable:
    def __init__(self):
        self.__elements = {}

    def __getitem__(self, key):
        return self.__elements[key]

    def __setitem__(self, key, value):
        self.__elements[key] = value

    def __delitem__(self, key):
        del self.__elements[key]

    def __iter__(self):
        self.iter = iter(self.__elements.values())
        return self

    def __next__(self):
        return next(self.iter)

    def __len__(self):
        return len(self.__elements)

    def __contains__(self, item):
        return item in self.__elements
