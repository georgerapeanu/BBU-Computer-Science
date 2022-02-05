from src.domain.DomainExceptions import GradeException, ValidatorException
from src.domain.GeneralValidator import GeneralValidator


class GradeValidator:
    @staticmethod
    def check_grade_id(grade_id):
        """Checks that grade_id is an integer. Raises GradeException if it is invalid

        :param grade_id: The grade id
        :type grade_id: int
        :return: None
        """

        try:
            GeneralValidator.check_id(grade_id)
        except ValidatorException as ex:
            raise GradeException(str(ex))

    @staticmethod
    def check_student_id(student_id):
        """Checks that student_id is an integer. Raises GradeException if it is invalid

        :param student_id: The student id
        :type student_id: int
        :return: None
        """

        try:
            GeneralValidator.check_id(student_id)
        except ValidatorException as ex:
            raise GradeException(str(ex))

    @staticmethod
    def check_discipline_id(discipline_id):
        """Checks that discipline_id is an integer. Raises GradeException if it is invalid

        :param discipline_id: The discipline id
        :type discipline_id: int
        :return: None
        """

        try:
            GeneralValidator.check_id(discipline_id)
        except ValidatorException as ex:
            raise GradeException(str(ex))

    @staticmethod
    def check_grade(grade):
        """Checks that grade is an integer between 0 and 10. Raises GradeException if not

        :param grade: the student grade
        :type grade: int
        :return: None
        """

        if type(grade) != int:
            raise GradeException("grade is not an integer")
        elif grade < 0 or grade > 10:
            raise GradeException("grade should be an integer between 0 and 10")

