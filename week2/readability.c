#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: \n");
    int textLength = strlen(text);
// basic values to use later
// needed as wordCoutn counts the ' ' so it will miss the 1st word
// (1)
    int wordCount = 1;
    int sentenceCount = 0;
    int letterCount = 0;

    for (int i = 0; i < textLength; i++){
        text[i] = tolower(text[i]);
        if (text[i] >= 'a' && text[i] <= 'z') // as everything is lowercase all letters have to be between a and z.
        {
            letterCount ++;
        }
        else if(text[i] == ' ') // assumes all words are seperated by spaces
        {
            wordCount ++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentenceCount ++;
        }
    }
    float index = 0.0588 * ((float) letterCount / (float) wordCount  * 100) - 0.296 * ((float) sentenceCount /
                (float) wordCount  * 100) - 15.8;
    index = round(index);
    if (index >= 0 && index < 16)
    {
        printf("Grade %i\n", (int) round(index));
    }
    else if (index < 0)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }

}

// (1) https://www.reddit.com/r/cs50/comments/ez9bpx/readability/