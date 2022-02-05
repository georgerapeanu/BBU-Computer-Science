import re
import subprocess
import traceback

from UI.Colors import Colors

from Domain.BattleshipOrientation import BattleshipOrientation
from Domain.DomainExceptions import AppException
from Domain.MoveStatus import MoveStatus
from Service.ModelAI import ModelAI
from Service.GameController import GameController
from Service.GenericPlayer import GenericPlayer


class UI:
    def __init__(self, player1, player2, game_controller):
        """Constructor for UI class

        :param player1: player 1 controller
        :type player1: GenericPlayer|AIModel
        :param player2: player 2 controller
        :type player2: GenericPlayer|ModelAI
        :param game_controller: game controller
        :type game_controller: GameController
        """
        self.__players = [player1, player2]
        self.__game_controller = game_controller

    def start(self):
        self.__place_battleships(0)
        self.__place_battleships(1)
        self.__play_game()

    def __display_board(self, battleship_board, move_board):
        for i in range(0, self.__game_controller.get_grid_size()):
            if i == 0:
                for j in range(0, 2 * self.__game_controller.get_grid_size() + 1):
                    print(Colors.WHITE + "-" + Colors.RESET, end="")
                print("")
            for j in range(0, self.__game_controller.get_grid_size()):
                if j == 0:
                    print(Colors.WHITE + "|" + Colors.RESET, end="")
                if (i, j) in move_board:
                    if move_board[(i, j)].status == MoveStatus.HIT:
                        print(Colors.RED + "X" + Colors.RESET, end="")
                    elif move_board[(i, j)].status == MoveStatus.MISS:
                        print(Colors.YELLOW + "O" + Colors.RESET, end="")
                    else:
                        raise Exception("App exception move is still pending")
                elif (i, j) in battleship_board:
                    print(Colors.BLUE + "#" + Colors.RESET, end="")
                else:
                    print(" ", end="")

                if (i, j) in battleship_board and \
                        (i, j + 1) in battleship_board and \
                        battleship_board[(i, j)] == battleship_board[(i, j + 1)]:
                    print(" ", end="")
                else:
                    print(Colors.WHITE + "|" + Colors.RESET, end="")
            print("")
            for j in range(0, 2 * self.__game_controller.get_grid_size() + 1):
                if j % 2 == 0:
                    print(Colors.WHITE + "-" + Colors.RESET, end="")
                    continue

                if (i, j // 2) in battleship_board and \
                        (i + 1, j // 2) in battleship_board and \
                        battleship_board[(i, j // 2)] == battleship_board[(i + 1, j // 2)]:
                    print(" ", end="")
                else:
                    print(Colors.WHITE + "-" + Colors.RESET, end="")
            print("")

    def __display_masked_board(self, player_id):
        battleship_board = {}
        move_board = {}
        for move in self.__players[1 - player_id].get_moves():
            move_board[(move.x, move.y)] = move

        self.__display_board(battleship_board, move_board)

    def __display_normal_board(self, player_id):
        battleship_board = {}
        for battleship in self.__players[player_id].get_battleships():
            if battleship.placed is False:
                continue
            for i in range(battleship.get_bounding_box()[0], battleship.get_bounding_box()[2] + 1):
                for j in range(battleship.get_bounding_box()[1], battleship.get_bounding_box()[3] + 1):
                    battleship_board[(i, j)] = battleship
        move_board = {}
        for move in self.__players[1 - player_id].get_moves():
            move_board[(move.x, move.y)] = move

        self.__display_board(battleship_board, move_board)

    def __display_battleship(self, battleship):
        if battleship.placed:
            orientation = ("horizontal" if battleship.orientation == BattleshipOrientation.HORIZONTAL else "vertical")
            print("%d. Battleship of size %d at %d %d with orientation %s" % (
                battleship.id, battleship.size, battleship.x, battleship.y, orientation))
        else:
            print("%d. Battleship of size %d" % (battleship.id, battleship.size))

    def __list_battleships(self, player_id):
        for battleship in self.__players[player_id].get_battleships():
            self.__display_battleship(battleship)

    def display_place_help(self):
        print("Battleship placing phase:")
        print("place {id} at {x} {y} {horizontal/vertical}: places the battleship with specified {id}")
        print("display grid: displays the current state of the grid")
        print("display battleships: displays the battleships at your disposition")
        print("reset battleship {id}: resets the battleship with {id} so it can be placed again")
        print("done: commits the battleship placement")
        print("help: displays help prompt")

    def display_last_move(self):
        move = self.__game_controller.get_last_move()
        status = ("HIT" if move.status == MoveStatus.HIT else "MISS")
        print("%s at %d %d!" % (status, move.x, move.y))
        if self.__game_controller.get_last_move_destroyed_battleship_size() is not None:
            print(
                "Destroyed a battleship of size %d!" % self.__game_controller.get_last_move_destroyed_battleship_size())

    def __place_battleships(self, player_id):
        print(Colors.RED + ("Player %d please place your battleships" % (player_id + 1)) + Colors.RESET)
        if isinstance(self.__players[player_id], ModelAI):
            self.__players[player_id].place_battleships()
            self.__game_controller.mark_done_placement(player_id)
            return
        commands = [
            "^ *place +[0-9]+ +at +[0-9]+ +[0-9]+ +(horizontal|vertical) *$",
            "^ *display +grid *$",
            "^ *display +battleships *$",
            "^ *reset +battleship +[0-9]+ *$",
            "^ *help *$",
            "^ *done *$"
        ]

        self.display_place_help()
        while True:
            try:
                command = input().strip()
                args = command.split(" ")
                if re.match(commands[0], command) is not None:
                    id = int(args[1])
                    x = int(args[3])
                    y = int(args[4])
                    orientation = args[5]
                    if orientation == "horizontal":
                        orientation = BattleshipOrientation.HORIZONTAL
                    else:
                        orientation = BattleshipOrientation.VERTICAL
                    self.__game_controller.place_player_battleship_from_raw(player_id, id, x, y, orientation)
                elif re.match(commands[1], command) is not None:
                    self.__display_normal_board(player_id)
                elif re.match(commands[2], command) is not None:
                    self.__list_battleships(player_id)
                elif re.match(commands[3], command) is not None:
                    id = int(args[2])
                    self.__game_controller.reset_battleship(player_id, id)
                elif re.match(commands[4], command) is not None:
                    self.display_place_help()
                elif re.match(commands[5], command) is not None:
                    self.__game_controller.mark_done_placement(player_id)
                    break
                else:
                    print(Colors.RED + "Invalid command" + Colors.RESET)
                    self.display_place_help()
            except AppException as ex:
                print("Error: " + str(ex))
                traceback.print_exc()
        subprocess.call("clear", shell=True)

    def __display_battleship_mask(self, battleship_mask):
        status = ("DEAD" if battleship_mask.destroyed else "ALIVE")
        print("%d. Battleship of size %d which is %s" % (battleship_mask.id, battleship_mask.size, status))

    def __list_battleship_masks(self, battleship_masks):
        for battleship_mask in battleship_masks:
            self.__display_battleship_mask(battleship_mask)

    def __process_player_move_command(self, commands):
        try:
            command = input().strip()
            args = command.split(" ")

            if re.match(commands[0], command) is not None:
                x = int(args[1])
                y = int(args[2])
                turn = self.__game_controller.get_turn()
                self.__game_controller.make_player_move_from_raw(turn, x, y)
                self.display_last_move()
            elif re.match(commands[1], command) is not None:
                self.__display_normal_board(self.__game_controller.get_turn())
            elif re.match(commands[2], command) is not None:
                self.__display_masked_board(1 - self.__game_controller.get_turn())
            elif re.match(commands[3], command) is not None:
                self.__list_battleship_masks(self.__game_controller.get_player_battleship_masks(self.__game_controller.get_turn()))
            elif re.match(commands[4], command) is not None:
                self.display_attack_help()
            else:
                print(Colors.RED + "Invalid command" + Colors.RESET)
                self.display_attack_help()
        except AppException as ex:
            print("Error: " + str(ex))

    def __process_ai_move(self, ai_player):
        """ Processes an AI shoot turn

        :param ai_player: AI player
        :type ai_player: ModelAI
        :return:
        """
        move = ai_player.get_best_move()
        self.__game_controller.make_player_move(move)
        self.display_last_move()
        ai_player.notify_last_move_destroyed_ship(self.__game_controller.get_last_move_destroyed_battleship_size())

    def display_attack_help(self):
        print("Attack phase:")
        print("shoot {x} {y}: shoots at cell {x}, {y}")
        print("display grid: displays the current state of the grid")
        print("display enemy grid: displays the enemy masked grid")
        print("display remaining battleships: displays the sizes of the remaining enemy battleship")
        print("help: displays help prompt")

    def __play_game(self):
        commands = [
            "^ *shoot +[0-9]+ +[0-9]+ *$",
            "^ *display +grid *$",
            "^ *display +enemy +grid *$",
            "^ *display +remaining +battleships *$",
            "^ *help *$"
        ]

        while self.__game_controller.get_winner() == -1:
            print(
                Colors.RED + ("Player %d please make a move" % (1 + self.__game_controller.get_turn())) + Colors.RESET)
            print("Opponent masked grid:")
            self.__display_masked_board(1 - self.__game_controller.get_turn())
            if isinstance(self.__players[self.__game_controller.get_turn()], ModelAI):
                self.__process_ai_move(self.__players[self.__game_controller.get_turn()])
            else:
                self.__process_player_move_command(commands)
            if self.__game_controller.get_last_move_destroyed_battleship_size() != None:
                tmp_size = self.__game_controller.get_last_move_destroyed_battleship_size()
                print(Colors.CYAN + ("Destoyed ship of size %d" % tmp_size) + Colors.RESET)

        print(Colors.GREEN + ("Player %d won!" % (self.__game_controller.get_winner() + 1)) + Colors.RESET)
