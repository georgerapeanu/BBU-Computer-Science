from src.domain.ActionLeaf import ActionLeaf


class ActionComposite:
    """This class defines the model of a composite action(composed of ActionLeafs or other ActionComposites
    """
    def __init__(self):
        self.__actions = []

    def add(self, action):
        """Adds an action to the current instance's actions

        :param action: the action to be added
        :type action: ActionLeaf|ActionComposite
        :return: None
        """
        self.__actions.append(action)

    def do_action(self):
        """Does the current action

        :return: None
        """
        for action in self.__actions:
            action.do_action()
