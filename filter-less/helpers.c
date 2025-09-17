#include "helpers.h"
#include <math.h>

int check(int a);
int average(int a, int b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            average = round(average / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) +
                                 (.189 * image[i][j].rgbtBlue));

            int sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) +
                                   (.168 * image[i][j].rgbtBlue));

            int sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) +
                                  (.131 * image[i][j].rgbtBlue));

            image[i][j].rgbtRed = check(sepiaRed);
            image[i][j].rgbtGreen = check(sepiaGreen);
            image[i][j].rgbtBlue = check(sepiaBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE a = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = a;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
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
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            for (int i_offset = -4; i_offset <= 4; i_offset++)
            {
                for (int j_offset = -4; j_offset <= 4; j_offset++)
                {
                    int new_i = i + i_offset;
                    int new_j = j + j_offset;

                    if (new_i >= 0 && new_i < height && new_j >= 0 && new_j < width)
                    {
                        sumRed += copy[new_i][new_j].rgbtRed;
                        sumGreen += copy[new_i][new_j].rgbtGreen;
                        sumBlue += copy[new_i][new_j].rgbtBlue;
                        count++;
                    }
                }
            }

            image[i][j].rgbtRed = average(sumRed, count);

            image[i][j].rgbtGreen = average(sumGreen, count);

            image[i][j].rgbtBlue = average(sumBlue, count);
        }
    }
}

// it makes sure that sepia isn't bigger than 255, aka 0xff.
int check(int a)
{
    if (a > 255)
    {
        a = 255;
        return a;
    }
    else
    {
        return a;
    }
}

int average(int a, int b)
{
    int j = round((float)a/b);
    return j;
}
