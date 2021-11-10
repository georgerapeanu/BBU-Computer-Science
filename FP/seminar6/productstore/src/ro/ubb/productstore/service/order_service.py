

class OrderService:
    def __init__(self, order_repository, product_repository):
        self.__order_repository = order_repository
        self.__product_repository = product_repository

   # def add(self, ):