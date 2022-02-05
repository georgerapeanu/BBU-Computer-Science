class OrderDTO:
    def __init__(self, product_name, product_quantity, cost):
        self.__product_name = product_name
        self.__product_quantity = product_quantity
        self.__cost = cost

    @property
    def product_name(self):
        return self.__product_name

    @product_name.setter
    def product_name(self, name):
        self.__product_name = name

    @property
    def product_quantity(self):
        return self.__product_quantity

    @property
    def cost(self):
        return self.__cost

    @cost.setter
    def cost(self, value):
        self.__cost = value


class OrderAssembler:
    @staticmethod
    def create_order_dto(product, order):
        return OrderDTO(product.name, order.quantity, product.price * order.quantity)

    @staticmethod
    def update_product(product, order_dto):
        pass

    @staticmethod
    def update_order(order, order_dto):
        pass
