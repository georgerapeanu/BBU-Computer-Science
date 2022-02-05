class ActionLeaf:
    """This class defines a basic action

    """
    def __init__(self, function, arguments):
        self.__function = function
        self.__arguments = arguments

    def do_action(self):
        """Does the current action

        :return: None
        """
        self.__function(*self.__arguments)
