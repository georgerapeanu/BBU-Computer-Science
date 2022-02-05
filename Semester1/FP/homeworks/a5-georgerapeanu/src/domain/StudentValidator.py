class StudentValidatorException(Exception):
    pass


class StudentValidator(object):
    @staticmethod
    def check_id(id):
        """validator for student id
        id should be a positive integer
        raises StudentValidatorException

        :param id: positive integer
        :type id: int
        :return: None
        """
        if type(id) != int:
            raise StudentValidatorException("id is not an integer")

        if id <= 0 :
            raise StudentValidatorException("id is not positive")

    @staticmethod
    def check_name(name):
        """validator for student name
        name should be a non-null string(ignoring whitespace)

        raises StudentValidatorException

        :param name: student name
        :type name: string
        :return: None
        """
        if type(name) != str:
            raise StudentValidatorException("name is not a string")

        if name.strip() == "":
            raise StudentValidatorException("name cannot be empty")

    @staticmethod
    def check_group(group):
        """validator for student group
        group should be a positive integer

        raises StudentValidatorException

        :param group:
        :type group: int
        :return: None
        """
        if type(group) != int:
            raise StudentValidatorException("group is not an integer")
        if group <= 0:
            raise StudentValidatorException("group is not positive")