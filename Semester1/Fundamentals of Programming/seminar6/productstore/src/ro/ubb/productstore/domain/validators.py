"""

@author: radu

 
"""


class ProductStoreException(Exception):
    pass


class ProductValidatorException(ProductStoreException):
    pass


class OrderValidatorException(ProductStoreException):
    pass


class ProductValidator:
    @staticmethod
    def validate(product):
        if product.price < 0:
            raise ProductValidatorException("The price cannot be negative.")


class OrderValidator:
    @staticmethod
    def validate(order):
        if order.quantity <= 0:
            raise OrderValidatorException("quantity cannot be negative")
