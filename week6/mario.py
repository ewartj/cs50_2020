from cs50 import get_int

def main():
    while True:
    # this do/wile loop from https://cs50.stackexchange.com/questions/32589/cs50-pset6-cash-py-not-returning-number-of-coins-used-for-change
        # https://www.reddit.com/r/cs50/comments/7tcnok/pset_6_need_help_with_mariopy_more_comfortable/
        user_input = input("Please give a height?\n")
        height = int(user_input) if user_input and user_input.isdigit() else -1
        if not height:
            print("Invalid number range.")
        if str(height).isalpha():
            print("Invalid number range.")
        elif not int(height) in range (1,9):
            print("Invalid number range.")
        elif int(height) >= 1 and int(height) <= 8:
            break
    mario(int(height))

def mario(n):
    for i in range(n + 1):
        hashes = n - (n - i)
        spaces = n - i
        print(" " * spaces, end= "")
        print("#" * hashes, end= "")
        print("  ", end= "")
        print("#" * hashes)


main()