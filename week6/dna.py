import csv
import pandas as pd
import re
from sys import argv, exit
from os import listdir
from os.path import isfile, join

def main():
    if len(argv) != 3:
        print("Please provide a database followed by a sequence to analyse \
                \n e.g: python dna.py test.csv dna.txt")
        exit(1)

    #1. open the csv reader
    df = pd.read_csv(argv[1])
    STPs = list(df.columns.values)
    del STPs[0]

    # method of filtering using pandas based on:
    # https://stackoverflow.com/questions/3207219/how-do-i-list-all-files-of-a-directory

    DNA_person = get_array(argv[2], STPs)
    df = df.loc[(df["AGATC"] == DNA_person["AGATC"]) & (df["TATC"] == DNA_person["TATC"]) & (df["AATG"] == DNA_person["AATG"])]

    if df.empty:
        print("No match")
    for i, row in df.iterrows():
        print(row["name"])


    # open the sequrnce
def openF(file):
    inputFile = file
    f = open(inputFile, "r")
    seq = f.read()
    seq = seq.replace("\n", "")
    f.close()
    return seq

def get_array(file, lst):
    name = file.split("ces/")[1]
    seq = openF(file)
    result = {}
    for i in range(len(lst)):
            # for i, c in enumerate('test'):
        name = lst[i]
        biggest = find_longest(seq, lst[i])
        result[name] = biggest
    return result

def find_longest(sequence, group):
    # based on code from:
    #https://stackoverflow.com/questions/62078827/how-to-catch-the-longest-sequence-of-a-group
    # build pattern
    pattern = fr"(?:{group})+"

    # iterate over all matches
    matches = (match[0] for match in re.finditer(pattern, sequence))

    # find the longest and get length
    total = max(matches, key=len)
    longest_length = len(total) / len(group)
    return longest_length


main()