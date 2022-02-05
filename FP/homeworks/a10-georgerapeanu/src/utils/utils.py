from copy import deepcopy


class Utils:
    @staticmethod
    def sort(iterable, compare):
        """Sorts the given iterable using gnome sort
            :param iterable: iterable
            :param compare: compare function

            :returns: list of sorted iterable items
        """
        iterable_list = [x for x in deepcopy(iterable)]
        pos = 0
        while pos < len(iterable_list):
            if pos == 0 or compare(iterable_list[pos], iterable_list[pos - 1]) is False:
                pos += 1
            else:
                (iterable_list[pos - 1], iterable_list[pos]) = (iterable_list[pos], iterable_list[pos - 1])
                pos -= 1
        return iterable_list

    @staticmethod
    def filter(iterable, accept):
        """Filters the given iterable

        """
        ans = []

        for item in iterable:
            if accept(item):
                ans.append(deepcopy(item))
        return ans
