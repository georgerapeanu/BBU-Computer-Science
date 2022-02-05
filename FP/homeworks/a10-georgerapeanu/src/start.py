from src.domain.Discipline import Discipline
from src.domain.Grade import Grade
from src.domain.Student import Student
from src.repository.BinaryRepository import BinaryRepository
from src.repository.GeneralRepository import GeneralRepository
from src.repository.TextFileRepository import TextFileRepository
from src.repository.UndoRepository import UndoRepository
from src.ui.UI import UI
from src.Settings import Settings


def add_entities(student_repository, discipline_repository, grade_repository):
    student_repository.add(Student(1, "AAA"))
    student_repository.add(Student(2, "BBB"))
    student_repository.add(Student(4, "CCC"))
    student_repository.add(Student(3, "DDD"))
    student_repository.add(Student(6, "ok"))

    discipline_repository.add(Discipline(1, "FP"))
    discipline_repository.add(Discipline(3, "ASC"))
    discipline_repository.add(Discipline(2, "Algebra"))
    discipline_repository.add(Discipline(5, "Analiza"))
    discipline_repository.add(Discipline(4, "nush"))

    grade_repository.add(Grade(1, 1, 1, 5))
    grade_repository.add(Grade(2, 3, 2, 1))
    grade_repository.add(Grade(3, 4, 5, 4))
    grade_repository.add(Grade(4, 6, 1, 10))
    grade_repository.add(Grade(5, 2, 3, 7))
    grade_repository.add(Grade(6, 3, 4, 7))
    grade_repository.add(Grade(7, 6, 4, 9))
    grade_repository.add(Grade(8, 4, 1, 10))
    grade_repository.add(Grade(9, 1, 1, 5))
    grade_repository.add(Grade(10, 1, 2, 10))


if __name__ == "__main__":
    settings = Settings()
    if settings.is_invalid():
        print("Error: invalid settings")
        exit(0)

    student_repository = None
    discipline_repository = None
    grade_repository = None
    undo_repository = None

    if settings.inmemory:
        student_repository = GeneralRepository(Student)
        discipline_repository = GeneralRepository(Discipline)
        grade_repository = GeneralRepository(Grade)
        add_entities(student_repository, discipline_repository, grade_repository)
    elif settings.binary:
        student_repository = BinaryRepository(Student, settings.students)
        discipline_repository = BinaryRepository(Discipline, settings.disciplines)
        grade_repository = BinaryRepository(Grade, settings.grades)
    else:
        student_repository = TextFileRepository(Student, settings.students)
        discipline_repository = TextFileRepository(Discipline, settings.disciplines)
        grade_repository = TextFileRepository(Grade, settings.grades)
    undo_repository = UndoRepository()
    ui = UI(student_repository, discipline_repository, grade_repository, undo_repository)
    ui.run()
