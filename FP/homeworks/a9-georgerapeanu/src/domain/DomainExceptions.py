class NonFatalException(Exception):
    pass


class FatalException(Exception):
    pass


class StudentException(NonFatalException):
    pass


class GradeException(NonFatalException):
    pass


class DisciplineException(NonFatalException):
    pass


class ValidatorException(NonFatalException):
    pass
