import traceback

from src.domain.Student import Student
from src.services.StudentService import StudentService
import re


class UI:

    def __init__(self):
        """This constructor initializes UI

        """
        self.student_service = StudentService(10)
        self.commands = [
            "^ *add +[0-9]+ +([a-z]|[A-Z])+ +[0-9]+ *$",
            "^ *list *$",
            "^ *filter +[0-9]+ *$",
            "^ *undo *$",
            "^ *exit *$",
            "^ *help *$"
        ]

    def print_error(self, s):
        """This function is used to print errors

        :param s: error
        :type s: string
        :return: None
        """
        print("Error: " + s)

    def print_help_prompt(self):
        """This function prints a help prompt

        :return: None
        """

        print("Ussage:")
        print("add id name group")
        print("\tadds a student with the specified id name and group")
        print("list")
        print("\tlists all current students")
        print("filter group")
        print("\tdeletes all students from the given group")
        print("undo")
        print("\tundoes the last add or filter operation")

    def print_students(self):
        """This function prints the current students

        :return: None
        """
        for student in self.student_service.get_students():
            print(student)

    def process_command(self, command):
        """This function processes a command given as a string

        :param command: command to parse
        :type command: string
        :return: None
        """

        args = command.strip().split(" ")

        try:
            if re.match(self.commands[0], command) is not None:
                id = int(args[1])
                name = str(args[2])
                group = int(args[3])
                self.student_service.add_student(id, name, group)
            elif re.match(self.commands[1], command) is not None:
                self.print_students()
            elif re.match(self.commands[2], command) is not None:
                group = int(args[1])
                self.student_service.filter(group)
            elif re.match(self.commands[3], command) is not None:
                self.student_service.undo()
            elif re.match(self.commands[4], command) is not None:
                exit(0)
            elif re.match(self.commands[5], command) is not None:
                self.print_help_prompt()
            else:
                raise Exception("Specified command does not exist")
        except Exception as ex:
            self.print_error(str(ex))
            self.print_help_prompt()

    def run(self):
        self.print_help_prompt()
        while True:
            command = input("Please enter your command: ")
            self.process_command(command)
