#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int count = 0;
    float cash = 0;
    do
        // Checks its a float > 0
    {
        // initially get the amount of change
        cash = get_float("Please input change owed:\n");
    }
    while (cash < 0.0);
    int cents = round(cash * 100);
    while (cents > 0)
    {
        //A series of while loops subtract each
        // coin tyoe starting with the largets
        while (cents >= 25)
        {
            cents -= 25;
            count ++;
        }
        while (cents >= 10)
        {
            cents -= 10;
            count ++;
        }
        while (cents >= 5)
        {
            cents -= 5;
            count ++;
        }
        while (cents >= 1)
        {
            cents -= 1;
            count ++;
        }
        printf("%i\n", count);
    }
}