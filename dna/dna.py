import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: dna.py CSVFILENAME textfilename")
        return 1

    # Read database file into a variable
    STR_COUNTS = {}

    with open(sys.argv[1]) as csv_file:
        reader = csv.DictReader(csv_file)
        for row in reader:
            name = row.pop("name")
            STR_COUNTS[name] = {key: int(value) for key, value in row.items()}

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as text_file:
        DNA_SEQUENCE = text_file.read().strip()


    # checks whether there are coincidences
    found_match = False

    for name, str_counts in STR_COUNTS.items():
        match = True

        for STR, count in str_counts.items():
            if longest_match(DNA_SEQUENCE, STR) != count:
                match = False
                break

        if match:
            print(name)
            found_match = True
            break

    if not found_match:
        print("No match")


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


main()
