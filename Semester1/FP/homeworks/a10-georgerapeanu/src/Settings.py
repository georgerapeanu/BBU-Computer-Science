class Settings:
    """This class loads the settings.properties file

    """

    def __init__(self):
        self.__repository = None
        self.__students = None
        self.__disciplines = None
        self.__grades = None
        f = open("settings.properties", "r")
        for line in f:
            args = line.strip().split("=", maxsplit=1)
            if len(args) != 2:
                continue
            args[0] = args[0].strip()
            args[1] = args[1].strip()
            if args[0] == "repository":
                if args[1] == "inmemory":
                    self.__repository = "inmemory"
                elif args[1] == "binaryfiles":
                    self.__repository = "binaryfiles"
                elif args[1] == "textfiles":
                    self.__repository = "textfiles"
            elif len(args[1]) < 2 or args[1][0] != '"' or args[1][-1] != '"':
                continue
            elif args[0] == "students":
                self.__students = args[1][1:-1]
            elif args[0] == "disciplines":
                self.__disciplines = args[1][1:-1]
            elif args[0] == "grades":
                self.__grades = args[1][1:-1]
        f.close()

    @property
    def repository(self):
        return self.__repository

    @property
    def students(self):
        return self.__students

    @property
    def disciplines(self):
        return self.__disciplines

    @property
    def grades(self):
        return self.__grades

    def is_invalid(self):
        if self.repository is None:
            return True
        if self.repository == "inmemory":
            return False
        if self.students is None or len(self.students) == 0:
            return True
        if self.disciplines is None or len(self.students) == 0:
            return True
        if self.grades is None or len(self.students) == 0:
            return True
        return False

    @property
    def inmemory(self):
        return self.repository == "inmemory"

    @property
    def binary(self):
        return self.repository == "binaryfiles"

    @property
    def text(self):
        return self.repository == "textfiles"
