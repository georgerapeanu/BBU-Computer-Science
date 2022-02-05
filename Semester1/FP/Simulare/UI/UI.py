import re

import texttable

from Domain.Exceptions import AppException
from Service.AI import AI
from Service.GameController import GameController


class UI:
    def __init__(self, game_controller, ai):
        """ Constructor for UI object

        :param game_controller: the game controller
        :type game_controller: GameController
        :param ai: AI
        :type ai: AI
        """

        self.__game_controller = game_controller
        self.__ai = ai
        self.__last_player_move = None
        self.__last_ai_move = None


    def __display_board(self):
        matrix = self.__game_controller.get_board_as_matrix()
        table = texttable.Texttable()
        table.set_cols_align(["m"] * 6)
        for row in matrix:
            table.add_row(row)
        print(table.draw())
        human_message = ""
        ai_message = ""
        if self.__last_player_move is not None:
            human_message = (" Human: (%d, %d, %s)" % (self.__last_player_move.x, self.__last_player_move.y, self.__last_player_move.value))
        if self.__last_ai_move is not None:
            ai_message = (" AI: (%d, %d, %s)" % (self.__last_ai_move.x, self.__last_ai_move.y, self.__last_ai_move.value))
        message = human_message
        if ai_message != "":
            message += ", " + ai_message
        if self.__game_controller.get_winner() == 0:
            print(message + "-win!")
        elif self.__game_controller.get_winner() == 1:
            print(message + "-lose!")
        else:
            print(message)

    def __declare_winner(self):
        print("Player #%d won!" % (self.__game_controller.get_winner() + 1))
        exit(0)

    def __do_ai_turn(self):
        move = self.__ai.get_move()
        self.__game_controller.process_move(move.id, move.x, move.y, move.value)
        self.__last_ai_move = move

    def __display_help_prompt(self):
        print("move x y O|X -> makes a move with specified id, coordinates and value")
        print("save -> saves the state of the game")
        print("help -> displays help")
        print("exit -> exit the game")

    def __do_player_turn(self):
        commands = [
            "^ *move +[0-9]+ +[0-9]+ +[OX] *$",
            "^ *save *$",
            "^ *help *$",
            "^ *exit *$"
        ]

        command = input("Enter command:").strip()
        while True:
            next_command = command.replace("  ", " ")
            if len(next_command) == len(command):
                break
            command = next_command

        if re.match(commands[0], command) is not None:
            args = command.strip().split(" ")
            id = self.__game_controller.get_next_id()
            x = int(args[1])
            y = int(args[2])
            value = args[3]
            self.__game_controller.process_move(id, x, y, value)
            self.__last_player_move = self.__game_controller.get_last_move()
        elif re.match(commands[1], command) is not None:
            self.__game_controller.save()
        elif re.match(commands[2], command) is not None:
            self.__display_help_prompt()
        elif re.match(commands[3], command) is not None:
            exit(0)
        else:
            print("invalid command")

    def run(self):
        while True:
            if self.__game_controller.get_winner() != -1 or self.__game_controller.get_turn() == 0:
                self.__display_board()
            if self.__game_controller.get_winner() != -1:
                self.__declare_winner()
            if self.__game_controller.get_turn() == 0:
                try:
                    self.__do_player_turn()
                except AppException as ex:
                    print(str(ex))
            else:
                self.__do_ai_turn()
