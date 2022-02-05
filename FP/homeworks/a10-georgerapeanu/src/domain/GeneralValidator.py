from src.domain.DomainExceptions import ValidatorException


class GeneralValidator:
    @staticmethod
    def check_id(id):
        """Checks that given id is an integer. Raises ValidatorException if it is invalid

        :param id: The id
        :type id: int
        :return: None
        """

        if type(id) != int:
            raise ValidatorException("id is not an int")

    @staticmethod
    def check_name(name):
        """Check if given name is nonempty. Raises ValidatorException if invalid

        :param name: the name of the student
        :type name: string
        :return: None
        """

        if type(name) != str:
            raise ValidatorException("name is not string")
        elif len(name.strip()) == 0:
            raise ValidatorException("name is empty")
