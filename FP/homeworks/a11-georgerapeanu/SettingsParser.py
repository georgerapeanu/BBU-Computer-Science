import ast


class SettingsParser:
    """This class loads the settings.properties file

    """

    def __init__(self, settings_file):
        self.__values = {}
        self.__values["player_types"] = ["Human", "Human"]
        with open(settings_file, "r") as f:
            for line in f:
                args = line.strip().split("=", maxsplit=1)
                if len(args) != 2:
                    continue
                args[0] = args[0].strip()
                args[1] = args[1].strip()
                value = None
                if args[0] == "grid_size":
                    value = int(args[1])
                elif args[0] == "battleship_sizes":
                    value = ast.literal_eval(args[1])
                elif args[0] == "player1":
                    self.__values["player_types"][0] = ast.literal_eval(args[1])
                    continue
                elif args[0] == "player2":
                    self.__values["player_types"][1] = ast.literal_eval(args[1])
                    pass
                else:
                    value = args[1]
                self.__values[args[0]] = value

    def __getitem__(self, item):
        return self.__values[item]
