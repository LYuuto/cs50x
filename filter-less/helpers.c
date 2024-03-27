#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = ((float)image[i][j].rgbtRed + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtBlue) / 3.0;
            average = round(average);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            float sepiaRed = round(0.393 * red + 0.769 * green + 0.189 * blue);
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            float sepiaGreen = round(0.349 * red + 0.686 * green + 0.168 * blue);
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            float sepiaBlue = round(0.272 * red + 0.534 * green + 0.131 * blue);
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image [i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

//blurring
int blurAction(int height, int width, RGBTRIPLE copy[height][width], char color, int i, int j)
{
    float sum = 0;
    int block_count = 0;

    //3x3 box
    for (int x = i - 1; x <= i + 1; x++)
    {
        for (int y = j - 1; y <= j + 1; y++)
        {
            if (x < 0 || x >= height || y < 0 || y >= width)
            {
                continue;
            }
            else
            {
                if (color == 'r')
                {
                    sum = sum + copy[x][y].rgbtRed;
                    block_count++;
                }
                else if (color == 'g')
                {
                    sum = sum + copy[x][y].rgbtGreen;
                    block_count++;
                }
                else if (color == 'b')
                {
                    sum = sum + copy[x][y].rgbtBlue;
                    block_count++;
                }
            }
        }
    }

    sum = round(sum / block_count);
    return sum;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    //save original rgb values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    //blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blurAction(height, width, copy, 'r', i, j);
            image[i][j].rgbtGreen = blurAction(height, width, copy, 'g', i, j);
            image[i][j].rgbtBlue = blurAction(height, width, copy, 'b', i, j);
        }
    }
    return;
}
