"""

@author: radu

 
"""
import re
import traceback


class Console:
    def __init__(self, product_service, order_service):
        self.__product_service = product_service
        self.__order_service = order_service
        self.__commands = [
            "^ *add +product +[0-9]+ +([a-z]|[A-Z])+ +(-)?[0-9]+ *$",
            "^ *list +products *$",
            "^ *add +order +[0-9]+ +[0-9]+ +(-)?[0-9]+ *$",
            "^ *list +orders *$",
            "^ *exit *$",
            "^ *filter +products +([a-z]|[A-Z])+ *$"
        ]

    def list_products(self, products):
        for product in products:
            print(str(product))

    def list_orders(self, orders):
        for order in orders:
            print(str(order))

    def run_command(self, command):
        args = command.split(" ")
        if re.match(self.__commands[0], command) is not None:
            self.__product_service.add_product(int(args[2]), args[3], int(args[4]))
        elif re.match(self.__commands[1], command) is not None:
            self.list_products(self.__product_service.get_all_products())
        elif re.match(self.__commands[2], command) is not None:
            self.__order_service.add_order(int(args[2]), int(args[3]), int(args[4]))
        elif re.match(self.__commands[3], command) is not None:
            self.list_orders(self.__order_service.get_all_orders())
        elif re.match(self.__commands[4], command) is not None:
            exit(0)
        elif re.match(self.__commands[5], command) is not None:
            self.list_products(self.__product_service.filter_by_name(args[2]))
        else:
            raise Exception("command does not exist")

    def run_console(self):
        # todo: implement menu/cmd-based ui
        while True:
            try:
                self.run_command(input("Please enter your command: "))
            except Exception as ex:
                print("Error: " + str(ex))
                print(traceback.print_exc())
