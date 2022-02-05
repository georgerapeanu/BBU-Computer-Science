class DistanceCalculator:
    @staticmethod
    def distance(a, b):
        """ Calculates the Manhattan distance between 2 points given as tuples

        :param a: first point
        :type a: tuple
        :param b: second point
        :type b: tuple
        :return:
        """

        return abs(a[0] - b[0]) + abs(a[1] - b[1])
