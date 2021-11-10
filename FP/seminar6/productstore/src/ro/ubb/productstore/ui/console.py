"""

@author: radu

 
"""
import re
import traceback


class Console:
    def __init__(self, product_service):
        self.__product_service = product_service
        self.__commands = [
            "^ *add +[0-9]* +([a-z]|[A-Z])+ +(-)?[0-9]* *$",
            "^ *list *$",
            "^ *exit *$"
        ]

    def list_products(self):
        for product in self.__product_service.get_all_products():
            print(str(product))

    def run_command(self, command):
        args = command.split(" ")
        if re.match(self.__commands[0], command) is not None:
            self.__product_service.add_product(int(args[1]), args[2], int(args[3]))
        elif re.match(self.__commands[1], command) is not None:
            self.list_products()
        elif re.match(self.__commands[2], command) is not None:
            exit(0)
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
