from src.domain.GradeValidator import GradeValidator


class Grade:
    """This class implements the grade class

    """
    def __init__(self, grade_id, student_id, discipline_id, grade):
        GradeValidator.check_grade_id(grade_id)
        GradeValidator.check_student_id(student_id)
        GradeValidator.check_discipline_id(discipline_id)
        self.__id = grade_id
        self.__student_id = student_id
        self.__discipline_id = discipline_id
        self.grade = grade

    @property
    def id(self):
        return self.__id

    @property
    def student_id(self):
        return self.__student_id

    @property
    def discipline_id(self):
        return self.__discipline_id

    @property
    def grade(self):
        return self.__grade

    @grade.setter
    def grade(self, grade):
        GradeValidator.check_grade(grade)
        self.__grade = grade

    def __eq__(self, other):
        return self.student_id == other.student_id and self.discipline_id == other.discipline_id and self.grade == other.grade

    def __str__(self):
        return "Grade #%d of student %d at %d : %d" % (self.id, self.student_id, self.discipline_id, self.grade)
