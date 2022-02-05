from Domain.Move import Move
from Repository.GeneralFileRepository import GeneralFileRepository
from Service.AI import AI
from Service.GameController import GameController
from UI.UI import UI

if __name__ == "__main__":
    move_repository = GeneralFileRepository(Move, "save")
    ai = AI(move_repository)
    game_controller = GameController(move_repository)
    ui = UI(game_controller, ai)
    load = input("load from last save?(yes/no)").strip()
    if load == "yes":
        move_repository.load()
    ui.run()
