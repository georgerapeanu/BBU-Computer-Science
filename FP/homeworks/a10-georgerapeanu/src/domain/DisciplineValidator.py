from src.domain.DomainExceptions import DisciplineException, ValidatorException
from src.domain.GeneralValidator import GeneralValidator


class DisciplineValidator:
    @staticmethod
    def check_id(id):
        """Checks if id is an integer. Raises DisciplineException if invalid

        :param id: the student id
        :type id: int
        :return: None
        """

        try:
            GeneralValidator.check_id(id)
        except ValidatorException as ex:
            raise DisciplineException(str(ex))

    @staticmethod
    def check_name(name):
        """Check if given name is nonempty. Raises DisciplineException if invalid

        :param name: the name of the student
        :type name: string
        :return: None
        """

        try:
            GeneralValidator.check_name(name)
        except ValidatorException as ex:
            raise DisciplineException(str(ex))
