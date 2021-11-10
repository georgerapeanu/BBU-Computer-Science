"""

@author: radu

 
"""


class ProductStoreException(Exception):
    pass


class ProductValidatorException(ProductStoreException):
    pass


class ProductValidator:
    #@staticmethod
    def validate(self, product):
        if product.price < 0:
            raise ProductValidatorException("The price cannot be negative.")

class OrderValidator:
    pass