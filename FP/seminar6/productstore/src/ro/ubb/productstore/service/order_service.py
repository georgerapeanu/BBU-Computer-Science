from functools import reduce

from ro.ubb.productstore.domain.entities import Order
from src.ro.ubb.productstore.repository.repository import Repository
from src.ro.ubb.productstore.domain.validators import ProductStoreException
from ro.ubb.productstore.domain.DTO import OrderDTO, OrderAssembler


class OrderServiceException(ProductStoreException):
    pass


class OrderService:
    def __init__(self, order_repository, product_repository):
        """

        :param order_repository:
        :type order_repository:Repository
        :param product_repository:
        :type product_repository: Repository
        """
        self.__order_repository = order_repository
        self.__product_repository = product_repository

    def add_order(self, order_id, product_id, quantity):
        if self.__product_repository.find_by_id(product_id) is None:
            raise OrderServiceException("product id doesn't exist")
        order = Order(order_id, product_id, quantity)
        self.__order_repository.save(order)

    def get_all_orders(self):
        return self.__order_repository.get_all()

    """
    def get_cost_of_orders(self):
        cost = 0
        for order in self.__order_repository.get_all():
            cost += order.quantity * self.__product_repository.find_by_id(order.product_id).price
        return cost
    """

    def __get_order_dtos(self):
        order_dtos = []
        for order in self.__order_repository.get_all():
            product = self.__product_repository.find_by_id(order.product_id)
            order_dtos.append(OrderAssembler.create_order_dto(product, order))
        return order_dtos

    """
    def get_cost_of_orders(self):
        cost = 0
        for order_dto in self.__get_order_dtos():
            cost += order_dto.cost
        return cost
    """

    def get_cost_orders(self):
        l = self.__get_order_dtos()
        return reduce(lambda x, y: x + y.cost, l, 0)
