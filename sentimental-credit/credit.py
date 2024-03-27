# TODO
from cs50 import get_int


def main():
    number = get_int("Number: ")
    validity = False
    cardtype = get_cardtype(number)

    if cardtype == "INVALID":
        print(cardtype)

    else:
        validity = checksum(number)
        if validity == True:
            print(cardtype)
        else:
            print("INVALID")


def get_cardtype(n):
    if (n >= (0.34*(10**15)) and n < (0.35*(10**15))) or (n >= (0.37*(10**15)) and n < (0.38*(10**15))):
        return "AMEX"

    if n >= (0.51*(10**16)) and n < (0.56*(10**16)):
        return "MASTERCARD"

    if (n >= (0.4*(10**13)) and n < (0.5*(10**13))) or (n >= (0.4*(10**16)) and n < (0.5*(10**16))):
        return "VISA"

    else:
        return "INVALID"


def checksum(n):
    sum = 0
    s = str(n)
    length = len(s)

    number = []
    for i in range(length):
        number.append(int(s[length-i-1]))

    for i in range(len(number)):
        if i % 2 == 0:
            sum += number[i]
        else:
            number[i] = number[i]*2
            if number[i] > 9:
                temp = str(number[i])
                number[i] = int(temp[0])+int(temp[1])
            sum += number[i]

    if sum % 10 == 0:
        return True
    else:
        return False


main()
