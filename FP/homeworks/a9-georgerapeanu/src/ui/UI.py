from src.domain.DomainExceptions import NonFatalException
from src.repository.GeneralRepository import GeneralRepository
from src.repository.UndoRepository import UndoRepository
from src.services.DisciplinesService import DisciplinesService
from src.services.GradesService import GradesService
from src.services.StudentsService import StudentsService
from src.services.UndoService import UndoService
from src.services.StatisticsService import StatisticsService
from src.ui.UIException import UIException
import re


class UI:
    """ this UI supports the following commands:
        -> add student/discipline id name
        -> update student/discipline id name
        -> delete student/discipline id
        -> list students/disciplines
        -> list students/disciplines id
        -> list students/disciplines name
        -> grade student_id discipline_id grade
        -> list failing students
        -> list best students
        -> list disciplines by average
        -> undo
        -> redo
        -> help
        -> exit
    """

    def print_error(self, s):
        print("Error: %s" % s)

    def print_help_prompt(self):
        print("USAGE: ")
        print("this UI supports the following commands:")
        print("-> add student/discipline id name")
        print("-> update student/discipline id name")
        print("-> delete student/discipline id")
        print("-> list students/disciplines")
        print("-> list students/disciplines id")
        print("-> list students/disciplines name")
        print("-> grade student_id discipline_id grade")
        print("-> list failing students")
        print("-> list best students")
        print("-> list disciplines by average")
        print("-> undo")
        print("-> redo")
        print("-> help")
        print("-> exit")

    def __init__(self, student_repository, discipline_repository, grade_repository, undo_repository):
        self.__students_service = StudentsService(student_repository, undo_repository)
        self.__disciplines_service = DisciplinesService(discipline_repository, undo_repository)
        self.__grades_service = GradesService(grade_repository, student_repository, discipline_repository, undo_repository)
        self.__undo_service = UndoService(undo_repository)
        self.__statistics_service = StatisticsService(student_repository, discipline_repository, grade_repository)
        self.__commands = [
            "^ *add +student +[0-9]+ +([a-z]|[A-Z])+ *$",
            "^ *add +discipline +[0-9]+ +([a-z]|[A-Z])+ *$",
            "^ *update +student +[0-9]+ +([a-z]|[A-Z])+ *$",
            "^ *update +discipline +[0-9]+ +([a-z]|[A-Z])+ *$",
            "^ *delete +student +[0-9]+ *$",
            "^ *delete +discipline +[0-9]+ *$",
            "^ *list +students *$",
            "^ *list +disciplines *$",
            "^ *list +students +[0-9]+ *$",
            "^ *list +disciplines +[0-9]+ *$",
            "^ *list +students +([a-z]|[A-Z])+ *$",
            "^ *list +disciplines +([a-z]|[A-Z])+ *$",
            "^ *grade +[0-9]+ +[0-9]+ +[0-9]+ *$",
            "^ *list +failing +students *$",
            "^ *list +best +students *$",
            "^ *list +disciplines +by +average *$",
            "^ *undo *$",
            "^ *redo *$",
            "^ *help *$",
            "^ *exit *$",
            "^ *list grades *$"
        ]

    def print_students(self, students):
        for student in students:
            print(student)

    def print_disciplines(self, disciplines):
        for discipline in disciplines:
            print(discipline)

    def print_grades(self, grades):
        for grade in grades:
            print(grade)

    def print_student_statistic(self, statistic):
        for entry in statistic:
            print(entry[0], end=" ")
            print("has average %f" % entry[1])

    def print_discipline_statistic(self, statistic):
        for entry in statistic:
            print(entry[0], end=" ")
            print("has average %f" % entry[1])

    def process_command(self, command):
        args = command.strip().split(" ")
        # "^ *add +student +[0-9]+ +([a-z]|[A-Z])+ *$",
        if re.match(self.__commands[0], command) is not None:
            self.__students_service.add_student(int(args[2]), args[3])
        # "^ *add +discipline +[0-9]+ +([a-z]|[A-Z])+ *$",
        elif re.match(self.__commands[1], command) is not None:
            self.__disciplines_service.add_discipline(int(args[2]), args[3])
        # "^ *update +student +[0-9]+ +([a-z]|[A-Z])+ *$",
        elif re.match(self.__commands[2], command) is not None:
            self.__students_service.update_student(int(args[2]), args[3])
        # "^ *update +discipline +[0-9]+ +([a-z]|[A-Z])+ *$",
        elif re.match(self.__commands[3], command) is not None:
            self.__disciplines_service.update_discipline(int(args[2]), args[3])
        # "^ *delete +student +[0-9]+ *$",
        elif re.match(self.__commands[4], command) is not None:
            self.__grades_service.delete_student(int(args[2]))
        # "^ *delete +discipline +[0-9]+ *$",
        elif re.match(self.__commands[5], command) is not None:
            self.__grades_service.delete_discipline(int(args[2]))
        # "^ *list +students *$",
        elif re.match(self.__commands[6], command) is not None:
            self.print_students(self.__students_service.list())
        # "^ *list +disciplines *$",
        elif re.match(self.__commands[7], command) is not None:
            self.print_disciplines(self.__disciplines_service.list())
        # "^ *list +students +[0-9]+ *$",
        elif re.match(self.__commands[8], command) is not None:
            print(self.__students_service.get_by_id(int(args[2])))
        # "^ *list +disciplines +[0-9]+ *$",
        elif re.match(self.__commands[9], command) is not None:
            print(self.__disciplines_service.get_by_id(int(args[2])))
        # "^ *list +students +([a-z]|[A-Z])+ *$",
        elif re.match(self.__commands[10], command) is not None:
            self.print_students(self.__students_service.list_by_name(args[2]))
        # "^ *list +disciplines +([a-z]|[A-Z])+ *$",
        elif re.match(self.__commands[11], command) is not None:
            self.print_disciplines(self.__disciplines_service.list_by_name(args[2]))
        # "^ *grade +[0-9]+ +[0-9]+ +[0-9]+ *$",
        elif re.match(self.__commands[12], command) is not None:
            self.__grades_service.add_grade(int(args[1]), int(args[2]), int(args[3]))
        # "^ *list +failing +students *$",
        elif re.match(self.__commands[13], command) is not None:
            self.print_students(self.__statistics_service.get_failing_students())
        # "^ *list +best +students *$",
        elif re.match(self.__commands[14], command) is not None:
            self.print_student_statistic(self.__statistics_service.get_best_students())
        # "^ *list +disciplines +by +average *$",
        elif re.match(self.__commands[15], command) is not None:
            self.print_discipline_statistic(self.__statistics_service.get_all_graded_disciplines())
        # "^ *undo *$",
        elif re.match(self.__commands[16], command) is not None:
            self.__undo_service.undo()
        # "^ *redo *$",
        elif re.match(self.__commands[17], command) is not None:
            self.__undo_service.redo()
        # "^ *help *$",
        elif re.match(self.__commands[18], command) is not None:
            self.print_help_prompt()
        # "^ *exit *$"
        elif re.match(self.__commands[19], command) is not None:
            exit(0)
        elif re.match(self.__commands[20], command) is not None:
            self.print_grades(self.__grades_service.list())
        else:
            raise UIException("Command is not recognized")

    def run(self):
        self.print_help_prompt()
        while True:
            command = input("Please enter your command: ")
            try:
                self.process_command(command)
            except NonFatalException as ex:
                self.print_error(str(ex))
                self.print_help_prompt()
