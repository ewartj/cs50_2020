#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h> //found on https://flaviocopes.com/c-boolean/

int main(int argc, char *argv[])
{
//open file
// 1. check theres only 2 arguments
    if (argc != 2)
    {
        printf("Please call a single file.");
        return 1;
    }

    //if fine set up the variables

    FILE *output = NULL;
    bool openFile = false;
    char fileName[8];
    int counter = 0;
    unsigned char buffer[512];

//2. loop through the file and count the jpegs
    //loop for start of jpeg "0xff0xd80xff0xe"
    // then make a new loop that opens each of these as seperate files
    //https://stackoverflow.com/questions/1835986/how-to-use-eof-to-run-through-a-text-file-in-c

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Cannot open file.");
        return 1;
    }

    while (fread(buffer, 512, 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //check if a jpg is currently being worked on
            if (openFile == true)
            {
                //If I'm working on a file close it
                fclose(output);
            }
            else
                // start working on a jpeg
            {
                openFile = true;
            }
            //write info to file
            sprintf(fileName, "%03i.jpg", counter);
            output = fopen(fileName, "w");
            counter ++;
        }
        if (openFile == true)
        {
            fwrite(&buffer, 512, 1, output);
        }
    }
    fclose(file);
    fclose(output);
    return 0;
}
