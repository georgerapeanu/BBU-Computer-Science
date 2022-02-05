"""

@author: radu

 
"""


class Product:
    def __init__(self, id, name, price):
        self.__id = id
        self.__name = name
        self.__price = price

    # def get_id(self):
    #     return self.__id
    #
    # def get_name(self):
    #     return self.__name
    #
    # def get_price(self):
    #     return self.__price
    #
    # def set_id(self, id):
    #     self.__id = id
    #
    # def set_name(self, name):
    #     self.__name = name
    #
    # def set_price(self, price):
    #     self.__price = price

    @property
    def id(self):
        return self.__id

    @id.setter
    def id(self, id):
        self.__id = id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        self.__name = name

    @property
    def price(self):
        return self.__price

    @price.setter
    def price(self, price):
        self.__price = price
