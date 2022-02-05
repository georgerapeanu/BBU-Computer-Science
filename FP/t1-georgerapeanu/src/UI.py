import functions
from datetime import datetime, timedelta


def ui_is_valid_number(number):
    """This function checks if a given number respects the rules from 1
    Being an UI function, the number should be provided as a string

    :param number: the number
    :type: string
    :return: True if the number is valid false otherwise
    """

    if len(number) != 4:
        return False

    if number[0] == '0':
        return False

    appeared = [False] * 10

    for digit in number:
        if ord(digit) < ord('0') or ord(digit) > ord('9'):
            return False
        if appeared[ord(digit) - ord('0')]:
            return False
        appeared[ord(digit) - ord('0')] = True

    return True


def ui_guess_is_cheat_code(guess):
    """This function checks if a given guess is in fact a cheat code

    :param guess:
    :type guess: str
    :return: True if guess is cheat code False otherwise
    """

    if guess == "8086":
        return True

    return False


def run_game():
    number = functions.get_valid_starting_number()
    start_time = datetime.now()
    total_time = timedelta(seconds=60)

    while True:
        str_guess = input("Please enter your guess:")
        if datetime.now() - start_time > total_time:
            print("Game lasted for more than 60 seconds. Computer wins!")
            break
        if ui_guess_is_cheat_code(str_guess):
            print("Hidden number is %d" % number)
            continue
        if not ui_is_valid_number(str_guess):
            print("Invalid guess, computer wins!")
            break
        guess = int(str_guess)
        if functions.is_correct_guess(number, guess):
            print("Number was correctly guessed. Human wins!")
            break
        codes = functions.get_guess_codes(number, guess)
        runners = functions.get_guess_runners(number, guess)
        print("Number of codes is %d and the number of runners is %d" % (codes, runners))
