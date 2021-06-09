from cs50 import get_float

def main():
    while True:
    # this do/wile loop from https://cs50.stackexchange.com/questions/32589/cs50-pset6-cash-py-not-returning-number-of-coins-used-for-change
        cash = get_float("Change owed: ")
        if cash >= 0:
            break
    cents = round(cash * 100)
    print(change(cents))

def change(cents):
    # based on my implementation of chash.c
    count = 0
    while cents > 0:
        if cents >= 25:
            cents -= 25
            count += 1
        elif cents >= 10:
            cents -= 10
            count += 1
        elif cents >= 5:
            cents -= 5
            count += 1
        elif cents >= 1:
            cents -= 1
            count += 1
    return count

main()