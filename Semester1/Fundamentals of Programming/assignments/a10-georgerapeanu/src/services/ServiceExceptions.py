from src.domain.DomainExceptions import NonFatalException


class StudentsServiceException(NonFatalException):
    pass


class DisciplinesServiceException(NonFatalException):
    pass


class GradesServiceException(NonFatalException):
    pass


class UndoServiceException(NonFatalException):
    pass
