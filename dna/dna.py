import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit()

    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as file:
        data = csv.reader(file)
        list_data = list(data)

    # list_data[0] = headers
    # list_date[0][0] = name

    # TODO: Read DNA sequence file into a variable
    sample = {}
    with open(sys.argv[2], "r") as f:
        reader = f.read()
        s = str(reader)

    # TODO: Find longest match of each STR in DNA sequence
    i = 0
    sample = {}
    head = list_data[0]
    head.remove(head[0])
    while i < len(head):
        tmp = count_word(s, head[i])
        tmp_dic = {head[i]: tmp}
        sample |= tmp_dic
        i += 1

    # TODO: Check database for matching profiles
    i = 1
    while i < len(list_data):
        check = 0
        j = 0
        while j < len(sample):
            if sample[head[j]] == int(list_data[i][j+1]):
                check += 1
                j += 1
            else:
                i += 1
                break
        if check == len(sample):
            print(list_data[i][0])
            break
    if check != len(sample):
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


# sadge brainstromed writing
# own to realize after that it was already written for me to use :"3
def count_word(stg, substg):
    i = 0
    count = 0
    temp = 0

    while i < len(stg) + 1:
        if stg[i:i+len(substg)] == substg:
            temp += 1
            i += len(substg)
        else:
            count = max(count, temp)
            temp = 0
            i += 1
    return count


main()
