from Domain.Battleship import Battleship
from Domain.BattleshipMask import BattleshipMask
from Domain.BattleshipOrientation import BattleshipOrientation
from Domain.GameData import GameData
from Domain.PlayerData import PlayerData
from Repository.GeneralRepository import GeneralRepository
from Service.RipAndTearAI import RipAndTearAI
from Service.GameController import GameController
from Service.GenericPlayer import GenericPlayer
from Service.RandomAI import RandomAI
from Service.SeekAndDestroyAI import SeekAndDestroyAI
from SettingsParser import SettingsParser
from UI.UI import UI


class Start:
    def __init__(self, settings_parser):
        self.__grid_size = settings_parser["grid_size"]
        self.__battleship_sizes = settings_parser["battleship_sizes"]
        self.__player_types = settings_parser["player_types"]

    def __create_player(self, player_type, player_data, game_data):
        if player_type == "RandomAI":
            return RandomAI(player_data, game_data)
        elif player_type == "SeekAndDestroyAI":
            return SeekAndDestroyAI(player_data, game_data)
        elif player_type == "RipAndTearAI":
            return RipAndTearAI(player_data, game_data)
        return GenericPlayer(player_data)

    def start(self):
        game_data = GameData(self.__grid_size, self.__battleship_sizes)
        p1_battleship_repository = GeneralRepository()
        p2_battleship_repository = GeneralRepository()
        p1_move_repository = GeneralRepository()
        p2_move_repository = GeneralRepository()
        p1_battleship_mask_repository = GeneralRepository()
        p2_battleship_mask_repository = GeneralRepository()
        for i in range(0, len(game_data.initial_battleships_sizes)):
            size = game_data.initial_battleships_sizes[i]
            p1_battleship_mask = BattleshipMask(i, size, False)
            p1_battleship = Battleship(i, size, False, 0, 0, BattleshipOrientation.VERTICAL, False)
            p2_battleship_mask = BattleshipMask(i, size, False)
            p2_battleship = Battleship(i, size, False, 0, 0, BattleshipOrientation.VERTICAL, False)
            p1_battleship_repository.add(p1_battleship)
            p2_battleship_repository.add(p2_battleship)
            p1_battleship_mask_repository.add(p2_battleship_mask)
            p2_battleship_mask_repository.add(p1_battleship_mask)
        p1_data = PlayerData(0, p1_battleship_repository, p1_move_repository, p1_battleship_mask_repository)
        p2_data = PlayerData(1, p2_battleship_repository, p2_move_repository, p2_battleship_mask_repository)

        player1 = self.__create_player(self.__player_types[0], p1_data, game_data)
        player2 = self.__create_player(self.__player_types[1], p2_data, game_data)

        game_controller = GameController(game_data, p1_data, p2_data)

        ui = UI(player1, player2, game_controller)
        ui.start()


if __name__ == "__main__":
    start = Start(SettingsParser("settings.properties"))
    start.start()
