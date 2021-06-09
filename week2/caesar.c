#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // check the corret number of arguments
    if (argc == 2)
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        // checking digit using loop based on:
        // https://www.reddit.com/r/cs50/comments/fgr1gw/pset_2_caesar_seems_to_work_but_not_passing/
        {
            if (isdigit(argv[1][i]) == false)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        int key = atoi(argv[1]);
        if (!(key > 0))
        {
            printf("Usage: ./caesar key");
            return 1;
        }
        else
        {
            string origText = get_string("plaintext: ");
            printf("ciphertext: ");
            for (int i = 0; i < strlen(origText); i++)
            {
                if ((islower(origText[i])))
                {
                    origText[i] = (((origText[i] + key) - 97) % 26  + 97);
                    printf("%c", origText[i]);
                }
                else if ((isupper(origText[i])))
                {
                    origText[i] = (((origText[i] + key) - 65) % 26  + 65);
                    printf("%c", origText[i]);
                }
                else
                {
                    printf("%c", origText[i]);
                }
            }
            printf("\n");
        }
        return 0;
    }
    else
    {
        printf("Usage: ./casesar \n");
        return 1;
    }
}
// (1)
// https://stackoverflow.com/questions/13188186/operator-in-c-not-greater-and-equal-to
