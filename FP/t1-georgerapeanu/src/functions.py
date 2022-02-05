import random


def get_valid_starting_number():
    """This function chooses a valid starting number

    :return: the chosen number
    :type: int
    """
    digits = [x for x in range(1, 10)]
    random.shuffle(digits)
    # this guarantees non zero starting number
    first_digit = digits[0]
    # eliminate the first used digit
    digits = digits[1:]
    # append 0 and re-shuffle the remaining digits
    digits.append(0)
    random.shuffle(digits)
    return first_digit * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3]


def get_guess_runners(number, guess):
    """This function determines the number of runners based on the hidden number and the guess

    :param number: the hidden number
    :type number: int
    :param guess: the user guess
    :type guess: int
    :return: the number of runners
    """

    appears_in_number = [False] * 10

    str_number = str(number)
    str_guess = str(guess)

    for i in range(0, len(str_number)):
        appears_in_number[ord(str_number[i]) - ord('0')] = True

    runners = 0

    for i in range(0, len(str_guess)):
        if appears_in_number[ord(str_guess[i]) - ord('0')] and str_number[i] != str_guess[i]:
            runners += 1

    return runners


def get_guess_codes(number, guess):
    """This function determines the number of codes based on the hidden number and the guess

    :param number: the hidden number
    :type number: int
    :param guess: the user guess
    :type guess: int
    :return: the number of codes
    """

    str_number = str(number)
    str_guess = str(guess)

    codes = 0

    for i in range(0, len(str_guess)):
        if str_number[i] == str_guess[i]:
            codes += 1

    return codes


def is_correct_guess(number, guess):
    """This function returns True if the human's guess is correct

    :param number: the hidden number
    :type number: int
    :param guess: the human guess
    :type guess: int
    :return: True if the guess is correct False otherwise
    """

    return True if number == guess else False
