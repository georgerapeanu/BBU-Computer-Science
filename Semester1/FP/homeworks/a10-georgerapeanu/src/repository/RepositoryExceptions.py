from src.domain.DomainExceptions import NonFatalException, FatalException


class GeneralRepositoryException(NonFatalException):
    pass


class UndoRepositoryException(NonFatalException):
    pass


class TextFileRepositoryException(FatalException):
    pass
