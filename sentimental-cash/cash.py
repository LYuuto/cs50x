# TODO
from cs50 import get_float


def main():
    count = 0
    number = get_input()*100

    count += number // 25
    number = number % 25

    count += number // 10
    number = number % 10

    count += number // 5
    number = number % 5

    count += number

    print(int(count))


def get_input():
    while True:
        number = get_float("Change owned: ")
        if number > 0:
            return number


main()