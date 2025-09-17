text = input("Text: ")

Coleman_index1 = 0.0588
Coleman_index2 = 0.296
Coleman_index3 = 15.8


def calculate_letters(text):
    num_letters = 0

    for character in text:
        if character.isalpha():
            num_letters += 1

    return num_letters


def calculate_words(text):
    num_words = 0

    for character in text:
        if character == " ":
            num_words += 1

    return num_words + 1


def calculate_sentences(text):
    num_sentences = 0

    for character in text:
        if character == "." or character == "?" or character == "!":
            num_sentences += 1

    return num_sentences


letters = float(calculate_letters(text))
words = float(calculate_words(text))
sentences = float(calculate_sentences(text))

value_letters = float((letters / words) * 100)
value_sentences = float((sentences / words) * 100)

coleman_index = round(Coleman_index1 * value_letters -
                      Coleman_index2 * value_sentences - Coleman_index3)

if coleman_index < 1:
    print("before grade 1.")
elif coleman_index > 16:
    print("Grade 16+.")
else:
    print(f"Grade {coleman_index}.")
