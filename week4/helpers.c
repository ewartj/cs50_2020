#include "helpers.h"
#include <math.h>

int cap(int uncapped);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    /// takre average of RGB at each pixel
    //  assign this as the value for that pixel
    // treat as an array hieght
    // newst array width in this this and run though
    //image[i][j].rgbtBlue ...
    float gray;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gray = round((image[i][j].rgbtGreen + image[i][j].rgbtRed + image[i][j].rgbtBlue)/3.000);
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtBlue = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
//  sepiaRed = .393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue
//   sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
//   sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    int sepBlue;
    int sepRed;
    int sepGreen;

    for (int i = 0; i < height; i++)
    {
        for (int j =0; j < width; j++)
        {
            sepBlue = cap(round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue));
            sepGreen = cap(round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue));
            sepRed = cap(round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue));

            image[i][j].rgbtBlue = sepBlue;
            image[i][j].rgbtGreen = sepGreen;
            image[i][j].rgbtRed = sepRed;

        }
    }
    return;
}

int cap(int uncapped)
{
    if(uncapped > 255)
    {
        uncapped = 255;
    }
    return uncapped;
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
//  used:
//     //https://cboard.cprogramming.com/c-programming/142074-how-flipping-image-horizontally.html
//     // https://www.reddit.com/r/cs50/comments/er30y5/cs50_2020_pset_4_reflect_help/
//    use of a temporary array to store the values
{
    int temp[3];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp[0] = image[i][j].rgbtBlue;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j -1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j -1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j -1].rgbtRed;

            image[i][width - j -1].rgbtBlue = temp[0];
            image[i][width - j -1].rgbtGreen = temp[1];
            image[i][width - j -1].rgbtRed = temp[2];
        }
    }
}
//Blur image
int getBlurValue(int i, int j,  int height, int width, RGBTRIPLE image[height][width], int RGB)
{
    int total = 0;
    float counter = 0;
    for (int k = i - 1; k < (i + 2); k++)
    {
        for (int l = j - 1; l < (j + 2); l++)
        {
            if (l < 0 || k < 0 || k >= height || l >= width)
            {

            }
            else
            {
                if (RGB == 0)
                {
                    total += image[k][l].rgbtRed;
                }
                else if (RGB == 1)
                {
                    total += image[k][l].rgbtBlue;
                }
                else
                {
                    total += image[k][l].rgbtGreen;
                }
                counter++;
            }

        }
    }
    return round(total / counter);
}
void blur(int height, int width, RGBTRIPLE image[height][width])
// idea of using two loops taken from
///https://www.reddit.com/r/cs50/comments/dqxbmr/i_need_help_refactoring_the_blur_function_of/
{

    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = getBlurValue(i, j, height, width, copy, 0);
            image[i][j].rgbtBlue = getBlurValue(i, j, height, width, copy, 1);
            image[i][j].rgbtGreen = getBlurValue(i, j, height, width, copy, 2);
        }
    }
    return;
}
