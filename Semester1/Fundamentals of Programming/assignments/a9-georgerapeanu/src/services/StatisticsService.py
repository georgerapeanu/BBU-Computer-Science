from src.repository.GeneralRepository import GeneralRepository


class StatisticsService:
    def __init__(self, student_repository, discipline_repository, grade_repository):
        """ Constructor for the statistics service

        :param student_repository: student repository
        :type student_repository: GeneralRepository
        :param discipline_repository: discipline repository
        :type discipline_repository: GeneralRepository
        :param grade_repository: grade repository
        :type grade_repository: GeneralRepository
        """

        self.__student_repository = student_repository
        self.__discipline_repository = discipline_repository
        self.__grade_repository = grade_repository

    def get_failing_students(self):
        """ This method get a list of all students that fail at at least one discipline

        :return: list of students
        """
        sum_of_grades = {}
        count_of_grades = {}

        for grade in self.__grade_repository.list():
            where = (grade.student_id, grade.discipline_id)
            if where not in sum_of_grades:
                sum_of_grades[where] = 0
                count_of_grades[where] = 0
            sum_of_grades[where] += grade.grade
            count_of_grades[where] += 1

        failing_students_ids = []

        for data in sum_of_grades.keys():
            if sum_of_grades[data] < count_of_grades[data] * 5:
                failing_students_ids.append(data[0])

        failing_students_ids = list(set(failing_students_ids))

        failing_students = []

        for id in failing_students_ids:
            failing_students.append(self.__student_repository.get_by_id(id))

        return failing_students

    def get_best_students(self):
        """ This method get the top students sorted decreasingly by their average over all disciplines.

        :return: list of tuples of students and average
        """

        sum_of_grades = {}
        count_of_grades = {}

        for grade in self.__grade_repository.list():
            where = (grade.student_id, grade.discipline_id)
            if where not in sum_of_grades:
                sum_of_grades[where] = 0
                count_of_grades[where] = 0
            sum_of_grades[where] += grade.grade
            count_of_grades[where] += 1

        average = {}
        count_of_disciplines = {}

        for data in sum_of_grades.keys():
            average[data[0]] = 0
            count_of_disciplines[data[0]] = 0

        for data in sum_of_grades.keys():
            average[data[0]] += sum_of_grades[data] / count_of_grades[data]
            count_of_disciplines[data[0]] += 1

        average_list = []
        for data in average.keys():
            average_list.append((data, average[data] / count_of_disciplines[data]))

        average_list.sort(key=(lambda x: x[1]), reverse=True)

        student_list = []

        for x in average_list:
            student_list.append((self.__student_repository.get_by_id(x[0]), x[1]))

        return student_list

    def get_all_graded_disciplines(self):
        """ This method returns all disciplines that have at least one grade sorted decreasingly
        by their average

        :return: list of tuples of disciplines and average
        """

        sum_of_grades = {}
        count_of_grades = {}

        for grade in self.__grade_repository.list():
            if grade.discipline_id not in sum_of_grades:
                sum_of_grades[grade.discipline_id] = 0
                count_of_grades[grade.discipline_id] = 0
            sum_of_grades[grade.discipline_id] += grade.grade
            count_of_grades[grade.discipline_id] += 1

        average_list = []

        for x in sum_of_grades.keys():
            average_list.append((x, sum_of_grades[x] / count_of_grades[x]))

        average_list.sort(key=(lambda x: x[1]), reverse=True)

        discipline_list = []
        for x in average_list:
            discipline_list.append((self.__discipline_repository.get_by_id(x[0]), x[1]))

        return discipline_list

