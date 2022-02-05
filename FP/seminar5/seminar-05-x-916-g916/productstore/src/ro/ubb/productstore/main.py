"""

@author: radu

 ProductStore

Write an application that manages the products and orders from a product store.
Product (product_id, name, price)
Order (order_id, product_id, quantity)

The application should allow to:

F1: add new products
F2: delete products
F3: update products
F4: print all products

F5: make an order
F6: delete an order
F7: update an order
F8: print all orders

F9: filter products (e.g: print all products whose name contain a given string)

F10: compute the cost of all orders
F11: filter orders (e.g:return all orders (crt., product name, quantity, cost) with the cost greater than 2)

F12_: validators and exceptions (ProductValidator)

F13_: class Order with properties

F14_: file repository

F15: find the product that was ordered most times.

F16: sort orders (product name, quantity, cost) descending after the cost (i.e., order cost) and alphabetically
after product name.

F17_: add __eq__ and __ne__
F18_: use validators (ProductValidator)

F19_: unittest

----------------------------------------------------------------------------------------------
I1: F1, F4
I2: F13_
I3: F12_, F9

I3.1: F17_, F18_

I4: F5, F8
I5: F10

I6: F11
I7: F15
I8: F16
I9: F19_
I10: F14_
I11: F2, F3, F6, F7



"""

"""
product = Product(1, "milk", 3)
product.set_price(4)
print(product.get_price())



product = Product(1, "milk", 3)
product.price = 4
print(product.price)
"""


if __name__ == '__main__':
    print("hello")
