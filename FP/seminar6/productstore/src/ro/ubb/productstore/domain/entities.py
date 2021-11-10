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
    # def set_id(self, id):
    #     self.__id = id
    #
    # def get_name(self):
    #     return self.__name
    #
    # def set_name(self, name):
    #     self.__name = name
    #
    # def get_price(self):
    #     return self.__price
    #
    # def set_price(self, price):
    #     self.__price = price
    #
    @property
    def id(self):
        return self.__id

    @id.setter
    def id(self, value):
        self.__id = id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        self.__name = value

    @property
    def price(self):
        return self.__price

    @price.setter
    def price(self, value):
        self.__price = value

    def __str__(self):
        return str(self.__id) + ". " + self.__name + " " + str(self.__price) + "$"


class Order:
    def __init__(self, order_id, product_id, quantity):
        self.id = order_id
        self.product_id = product_id
        self.quantity = quantity

    @property
    def id(self):
        return self.__id

    @id.setter
    def id(self, value):
        self.__id = value

    @property
    def product_id(self):
        return self.__product_id

    @product_id.setter
    def product_id(self, value):
        self.__product_id = value

    @property
    def quantity(self):
        return self.__quantity

    @quantity.setter
    def quantity(self, value):
        self.__quantity = value
