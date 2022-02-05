from Domain.DomainExceptions import AppException


class RepositoryException(AppException):
    pass


class GeneralRepositoryException(RepositoryException):
    pass
