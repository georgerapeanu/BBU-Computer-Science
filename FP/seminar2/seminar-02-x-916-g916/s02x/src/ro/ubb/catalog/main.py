"""

@author: radu


Write an application which manages the students of a faculty.
Each student has a unique id, a name and a grade. The application should
allow to:

F1: print all students
F2: add students
F3: delete students
F4: show students whose grades are >= a given value
F5: find a student with the maximal grade
F6_: split the application into modules (main, ui, domain, util)
F7_: validate input data
F8_: student_id is unique - validation in add, delete etc.
F9: find all students whose name contain a string t (the match should not be
    case sensitive)
F10: undo
F11: remove all students with the grade smaller than 5 (using TDD)
F12: sort students according to their grade (descending)  (using TDD)
F13: given an integer 'nr', find the top nr students according
     to their grade  (using TDD)
F14: compute the average grade of all students having the grade >= 5 (using TDD)
F15: sort all students according to their grade and alphabetically (using TDD).
F16_: testing (assert)
F17_: cmd-based ui
------------

I1: F2, F1, F3, F4, F5
I2: F6_, F7_
I3: F8_, F9
I4: F10
I5: F11, F12, F13, F14, F15
-----------

I1: F2, F1, F3, F4, F5
I2: F6_, F7_
I3: F8_, F9
I4: F10
I5: F11, F12, F13, F14, F15

--------------
sem3:
- cmd-based ui
- exceptions/validations
- testing

I1: F2, F1
*I2: F7_, F8_, F16_, F17_
I3: F8_, F9, F3, F4, F5, F6_
I4: F10
I5: F11, F12, F13, F14, F15

 
"""

# # =======DOMAIN=======
#
# def create_student(id, name, grade):
#     """
#     Creates a new student
#     :param id:
#     :param name:
#     :param grade:
#     :return: a dictionary with the keys
#     """
#     return {
#         "id": id,
#         "name": name,
#         "grade": grade
#     }
#
#
# def get_id(student):
#     return student["id"]
#
#
# def get_name(student):
#     return student["name"]
#
#
# def get_grade(student):
#     return student["grade"]
#
#
# def set_id(student, id):
#     student["id"] = id
#
#
# def set_name(student, name):
#     student["name"] = name
#
#
# def set_grade(student, grade):
#     student["grade"] = grade
#
#
# # ======operations======
#
#
# def add_student(students, id, name, grade):
#     student = create_student(id, name, grade)
#     students.append(student)
#
#
# def find_by_id(students, id):
#     result = list(filter(lambda x: get_id(x) == id, students))
#     return result[0] if len(result) > 0 else None
#
#
# # =======UI========
#
# # def ui_add_student(students):
# #     id = int(input("Enter the id: "))
# #     name = input("Enter the name: ")
# #     grade = int(input("Enter the grade: "))
# #     add_student(students, id, name, grade)
#
#
# def print_menu_options():
#     print("1: Add student\n"
#           "2: Print all students\n"
#           "x: Exit"
#           )
#
#
# def print_all_students(students):
#     print(students)
#
#
# def run_menu():
#     students = []
#     options = {
#         1: ui_add_student,
#         2: print_all_students
#     }
#     while True:
#         print_menu_options()
#         opt = input("Option: ")
#         if opt == "x":
#             break
#         opt = int(opt)
#         # if opt==1:
#         #    ui_add_student(students)
#         # if opt==2:
#         #    print_all_students(students)
#         options[opt](students)
#
#
# ===== DOMAIN ============================
import traceback


def create_student(id, name, grade):
    """ Creates a new student
    :param id:
    :param name:
    :param grade:
    :return: A dictionary with the keys
    """
    return {
        "id": id,
        "name": name,
        "grade": grade
    }


def get_id(student):
    return student["id"]


def get_name(student):
    return student["name"]


def get_grade(student):
    return student["grade"]


def set_id(student, id):
    student["id"] = id


def set_name(student, name):
    student["name"] = name


def set_grade(student, grade):
    student["grade"] = grade


# ===== OPERATIONS ============================

def add_student(students, id, name, grade):
    """ ... """
    # TODO: Check if 'id' is unique
    student = create_student(id, name, grade)
    students.append(student)


def find_by_id(students, id):
    #                        x is a student
    result = list(filter(lambda x: get_id(x) == id, students))
    return result[0] if len(result) > 0 else None


# ==================== UI =====================

def ui_add_student(students, id, name, grade):
    # id = int(input("Enter the id: "))
    # name = input("Enter the name: ")
    # grade = int(input("Enter the grade: "))
    # try:
    #     id = int(id)
    # except ValueError as ve:
    #     print("Id must be an int:", ve)
    # grade = int(grade)
    #
    try:
        add_student(students, int(id), name, int(grade))
    except ValueError as ve:
        print("Id and grade must be int: ", ve)


def print_menu_options():
    print("1: Add student\n"
          "2: Print all students\n"
          "x: Exit")


def print_all_students(students):
    print(students)
    # TODO: print students in a more user-friendly format


def print_commands(commands):
    print(*list(commands.keys()), "exit", sep="\n")


def get_command_and_args(cmd_line):
    # add id, name, grade
    # print
    position = cmd_line.find(" ")
    if position == -1:
        return cmd_line, []
    cmd_name = cmd_line[:position]
    args = cmd_line[position:].split(",")
    args = [arg.strip() for arg in args]
    return cmd_name, args


def run_menu_cmd():
    # add id, name, grade
    # print
    # exit
    students = []
    commands = {
        "add": ui_add_student,
        "print": print_all_students
    }

    while True:
        print_commands(commands)
        cmd_line = input("Input the command and args: ")
        if cmd_line == "exit":
            break
        cmd, args = get_command_and_args(cmd_line)
        try:
            commands[cmd](students, *args)
        except KeyError:
            print(f"Option {cmd} is not yet implemented")
        except ValueError as ve:
            print("The following exception was thrown: ", ve)
            traceback.print_exc()


# def run_menu():
#     students = []
#     options = {
#         1: ui_add_student,  # don't call the function!
#         2: print_all_students
#     }
#     while True:
#         print_menu_options()
#         opt = input("Option: ")
#         if opt == "x":
#             break
#         opt = int(opt)
#         # UGLY (if it's growing)
#         # if opt == 1:
#         #     ui_add_student(students)
#         # if opt == 2:
#         #     print_all_students(students)
#         # PRETTY:
#         options[opt](students)  # ui_add_student(students) or print_all_students(students) etc


# ==================TESTS============
def set_up():
    students = []
    add_student(students, 1, "Alex", 1)
    add_student(students, 2, "Radu", 2)
    return students


def test_add_student():
    # assert False
    students = set_up()
    add_student(students, 3, "new student", 10)
    assert len(students) == 3
    # TODO: test the exceptions


def test_all():
    test_add_student()


if __name__ == '__main__':
    test_all()
    try:
        run_menu_cmd()
    except Exception as ex:
        print("Unknown exception caught: ", ex)
        traceback.print_exc()

    # run_menu()
