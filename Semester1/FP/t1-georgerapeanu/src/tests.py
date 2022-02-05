import functions
import UI


def test_ui_is_valid_number():
    valid_examples = ["1234", "1984", "1980", "1024"]
    invalid_examples = ["3435", "2001", "0123", "8888"]

    for x in valid_examples:
        assert(UI.ui_is_valid_number(x))

    for x in invalid_examples:
        assert(not UI.ui_is_valid_number(x))


def test_get_valid_starting_number():
    for i in range(0, 2000):
        number = functions.get_valid_starting_number()
        # kinda cheating
        assert UI.ui_is_valid_number(str(number))


def test_get_guess_runners():
    assert(functions.get_guess_runners(5873, 9624) == 0)
    assert(functions.get_guess_runners(5873, 1234) == 1)
    assert(functions.get_guess_runners(5873, 3257) == 3)
    assert(functions.get_guess_runners(5873, 3875) == 2)


def test_get_guess_codes():
    assert(functions.get_guess_codes(5873, 9624) == 0)
    assert(functions.get_guess_codes(5873, 1234) == 0)
    assert(functions.get_guess_codes(5873, 3257) == 0)
    assert(functions.get_guess_codes(5873, 3875) == 2)


def run_tests():
    test_ui_is_valid_number()
    test_get_valid_starting_number()
    test_get_guess_runners()
    test_get_guess_codes()


if __name__ == "__main__":
    run_tests()