#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height, i, j;
    //a do while loop to only allow values between 1 and 8
    do
    {
        height = get_int("Please give a height?\n");
    }
    while (height < 1 || height > 8);
    for (i = 0; i < height; i++)
    {
        // print space before the hashes, the condition height -i -1
        // subtracts the space needed for hashes
        // (and caccounts for C starting from 0 not 1)
        for (j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        for (j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("%*c", 2, ' ');
        //print second set of hashes
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}