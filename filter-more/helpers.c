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

//edge
int edgeAction(int height, int width, RGBTRIPLE copy[height][width], char color, int i, int j)
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    float sumX = 0;
    float sumY = 0;

    for (int x = i - 1, a = 0; x <= i + 1; x++, a++)
    {
        for (int y = j - 1, b = 0; y <= j + 1; y++, b++)
        {
            if (x < 0 || x >= height || y < 0 || y >= width)
            {
                continue;
            }
            if (color == 'r')
            {
                sumX = sumX + copy[x][y].rgbtRed * gx[a][b];
                sumY = sumY + copy[x][y].rgbtRed * gy[a][b];
            }
            else if (color == 'g')
            {
                sumX = sumX + copy[x][y].rgbtGreen * gx[a][b];
                sumY = sumY + copy[x][y].rgbtGreen * gy[a][b];
            }
            else if (color == 'b')
            {
                sumX = sumX + copy[x][y].rgbtBlue * gx[a][b];
                sumY = sumY + copy[x][y].rgbtBlue * gy[a][b];
            }
        }
    }

    int sum = round(sqrt((sumX * sumX) + (sumY * s
    umY)));

    if (sum > 255)
    {
        sum = 255;
    }


    return sum;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int finalred[height][width];
    int finalgreen[height][width];
    int finalblue[height][width];


    //save original rgb values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    //edge
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = edgeAction(height, width, copy, 'r', i, j);
            image[i][j].rgbtGreen = edgeAction(height, width, copy, 'g', i, j);
            image[i][j].rgbtBlue = edgeAction(height, width, copy, 'b', i, j);
        }
    }
    return;
}
