import re

from cs50 import get_string

def main():
    text = get_string("Please input text:\n")
    readability(text)

def readability(text):
    letter_count = 0.0
    word_count = 1.0
    sentence_count = 0.0
    for i in text:
        # next line from https://www.tutorialgateway.org/python-program-to-check-character-is-alphabet-or-not/
        if i.isalpha():
            letter_count += 1
        elif i.isspace():
            word_count += 1
        # elif i == ('.' or '!' or '?'):
    sentence_count += len(re.findall(r'\.!?', text))# += 1
    print(f"letters: {letter_count}")
    print(f"words {word_count}")
    print(f"sentences {sentence_count}")

    index = 0.0588 * ( letter_count / word_count * 100) - 0.296 * (sentence_count /
            word_count * 100) - 15.8
    print("Index:")
    print(index)

    if index < 1:
        print("Before Grade 1")
    elif (index > 16):
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")

main()