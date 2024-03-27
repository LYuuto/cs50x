# TODO
from cs50 import get_int


def main():
    number = get_height()
    for i in range(number):
        print(" "*(number-i-1), end="")
        print("#"*(i+1), end="")
        print()


def get_height():
    while True:
        number = get_int("Height: ")
        if number > 0 and number < 9:
            return number


main()

