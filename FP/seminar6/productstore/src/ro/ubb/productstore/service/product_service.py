"""

@author: radu

 
"""
from ro.ubb.productstore.domain.entities import Product


class ProductService:
    def __init__(self, repository):
        self.__repository = repository

    def add_product(self, product_id, name, price):
        new_product = Product(product_id, name, price)
        self.__repository.save(new_product)

    def get_all_products(self):
        return self.__repository.get_all()