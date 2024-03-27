# TODO
from cs50 import get_string


def main():
    text = get_string("Text: ")
    index = formula(text)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def formula(text):
    letter_count = 0
    word_count = 1
    sentence_count = 0

    for i in range(len(text)):
        if text[i] == " ":
            word_count += 1
        elif text[i] == "." or text[i] == "!" or text[i] == "?":
            sentence_count += 1
        elif (ord(text[i]) > 64 and ord(text[i]) < 90) or (ord(text[i]) > 96 and ord(text[i]) < 123):
            letter_count += 1

    L = (letter_count / word_count) * 100
    S = (sentence_count / word_count) * 100
    index = 0.0588 * L - 0.296 * S - 15.8

    return round(index)


main()