#pragma once

#include "helpers.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <stdint.h>
#include <math.h>
#include <cmath>

// Convert image to grayscale
void grayscale(int height, int width, std::vector<std::vector<RGBTRIPLE>>& image)
{
    std::vector<std::vector<RGBTRIPLE>>temp = image;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = (temp[i][j].rgbtBlue + temp[i][j].rgbtGreen + temp[i][j].rgbtRed) / 3;
            image[i][j].rgbtGreen = (temp[i][j].rgbtBlue + temp[i][j].rgbtGreen + temp[i][j].rgbtRed) / 3;
            image[i][j].rgbtRed = (temp[i][j].rgbtBlue + temp[i][j].rgbtGreen + temp[i][j].rgbtRed) / 3;
        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, std::vector<std::vector<RGBTRIPLE>> &image)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width-1; j<width/2; j++, k--)
        {
            std::swap(image[i][j], image[i][k]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width,  std::vector<std::vector<RGBTRIPLE>> &image)
{
    std::vector<std::vector<RGBTRIPLE>>temp = image;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {      
            if (i - 1 >= 0 && j - 1 >= 0 && j + 1 < width && i + 1 < height)
            {
                image[i][j].rgbtBlue = (temp[i][j].rgbtBlue + temp[i][j + 1].rgbtBlue + temp[i][j - 1].rgbtBlue + temp[i - 1][j].rgbtBlue +
                    temp[i + 1][j].rgbtBlue + temp[i - 1][j - 1].rgbtBlue + temp[i - 1][j + 1].rgbtBlue + temp[i + 1][j - 1].rgbtBlue + temp[i + 1][j + 1].rgbtBlue) / 9;

                image[i][j].rgbtGreen = (temp[i][j].rgbtGreen + temp[i][j + 1].rgbtGreen + temp[i][j - 1].rgbtGreen + temp[i - 1][j].rgbtGreen +
                    temp[i + 1][j].rgbtGreen + temp[i - 1][j - 1].rgbtGreen + temp[i - 1][j + 1].rgbtGreen + temp[i + 1][j - 1].rgbtGreen + temp[i + 1][j + 1].rgbtGreen) / 9;

                image[i][j].rgbtRed = (temp[i][j].rgbtRed + temp[i][j + 1].rgbtRed + temp[i][j - 1].rgbtRed + temp[i - 1][j].rgbtRed +
                    temp[i + 1][j].rgbtRed + temp[i - 1][j - 1].rgbtRed + temp[i - 1][j + 1].rgbtRed + temp[i + 1][j - 1].rgbtRed + temp[i + 1][j + 1].rgbtRed) / 9;
            }
        }
    }
    return;
}


// Detect edges
void edges(int height, int width, std::vector<std::vector<RGBTRIPLE>> &image)
{
    int tempint = 0;
    int tempint2 = 0;

    std::vector<std::vector<RGBTRIPLE>> temp = image;


    std::vector<int>Gx({ -1,0,1,
                          -2, 0, 2,
                          -1, 0, 1});

    std::vector<int>Gy({ -1, -2,-1 ,
                           0,0,0 ,            
                          1, 2, 1});


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i - 1 >= 0 && j - 1 >= 0 && j + 1 < width && i + 1 < height)
            {
                //Blue
                tempint = 0;
                tempint2 = 0;

                tempint = temp[i - 1][j - 1].rgbtBlue * Gx[0] + temp[i - 1][j].rgbtBlue * Gx[1] + temp[i - 1][j + 1].rgbtBlue * Gx[2] +
                    temp[i][j - 1].rgbtBlue * Gx[3] + temp[i][j].rgbtBlue * Gx[4] + temp[i][j + 1].rgbtBlue * Gx[5] +
                    temp[i + 1][j - 1].rgbtBlue * Gx[6] + temp[i + 1][j].rgbtBlue * Gx[7] + temp[i + 1][j + 1].rgbtBlue * Gx[8];

                tempint2 = temp[i - 1][j - 1].rgbtBlue * Gy[0] + temp[i - 1][j].rgbtBlue * Gy[1] + temp[i - 1][j + 1].rgbtBlue * Gy[2] +
                    temp[i][j - 1].rgbtBlue * Gy[3] + temp[i][j].rgbtBlue * Gy[4] + temp[i][j + 1].rgbtBlue * Gy[5] +
                    temp[i + 1][j - 1].rgbtBlue * Gy[6] + temp[i + 1][j].rgbtBlue * Gy[7] + temp[i + 1][j + 1].rgbtBlue * Gy[8];

                if (0 < sqrt(tempint * tempint + tempint2 * tempint2) < 255)
                    image[i][j].rgbtBlue = round(sqrt(tempint * tempint + tempint2 * tempint2));

                if (0 > sqrt(tempint * tempint + tempint2 * tempint2))
                {
                    image[i][j].rgbtBlue = 0;
                 }
                if (255 < sqrt(tempint * tempint + tempint2 * tempint2))
                {
                    image[i][j].rgbtBlue = 255;
                }

                //Green
                tempint = 0;
                tempint2 = 0;


                tempint = temp[i - 1][j - 1].rgbtGreen * Gx[0] + temp[i - 1][j].rgbtGreen * Gx[1] + temp[i - 1][j + 1].rgbtGreen * Gx[2] +
                    temp[i][j - 1].rgbtGreen * Gx[3] + temp[i][j].rgbtGreen * Gx[4] + temp[i][j + 1].rgbtGreen * Gx[5] +
                    temp[i + 1][j - 1].rgbtGreen * Gx[6] + temp[i + 1][j].rgbtGreen * Gx[7] + temp[i + 1][j + 1].rgbtGreen * Gx[8];

                tempint2 = temp[i - 1][j - 1].rgbtGreen * Gy[0] + temp[i - 1][j].rgbtGreen * Gy[1] + temp[i - 1][j + 1].rgbtGreen * Gy[2] +
                        temp[i][j - 1].rgbtGreen * Gy[3] + temp[i][j].rgbtGreen * Gy[4] + temp[i][j + 1].rgbtGreen * Gy[5] +
                        temp[i + 1][j - 1].rgbtGreen * Gy[6] + temp[i + 1][j].rgbtGreen * Gy[7] + temp[i + 1][j + 1].rgbtGreen * Gy[8];

                if (0 < sqrt(tempint * tempint + tempint2 * tempint2) < 255)
                    image[i][j].rgbtGreen = round(sqrt(tempint * tempint + tempint2 * tempint2));

                if (0 > sqrt(tempint * tempint + tempint2 * tempint2))
                {
                    image[i][j].rgbtGreen = 0;
                }
                if (255 < sqrt(tempint * tempint + tempint2 * tempint2))
                {
                    image[i][j].rgbtGreen = 255;
                }

                //Red
                tempint = 0;
                tempint2 = 0;

                    tempint = temp[i - 1][j - 1].rgbtRed * Gx[0] + temp[i - 1][j].rgbtRed * Gx[1] + temp[i - 1][j + 1].rgbtRed * Gx[2] +
                    temp[i][j - 1].rgbtRed * Gx[3] + temp[i][j].rgbtRed * Gx[4] + temp[i][j + 1].rgbtRed * Gx[5] +
                    temp[i + 1][j - 1].rgbtRed * Gx[6] + temp[i + 1][j].rgbtRed * Gx[7] + temp[i + 1][j + 1].rgbtRed * Gx[8];

                tempint2 = temp[i - 1][j - 1].rgbtRed * Gy[0] + temp[i - 1][j].rgbtRed * Gy[1] + temp[i - 1][j + 1].rgbtRed * Gy[2] +
                        temp[i][j - 1].rgbtRed * Gy[3] + temp[i][j].rgbtRed * Gy[4] + temp[i][j + 1].rgbtRed * Gy[5] +
                        temp[i + 1][j - 1].rgbtRed * Gy[6] + temp[i + 1][j].rgbtRed * Gy[7] + temp[i + 1][j + 1].rgbtRed * Gy[8];

                if (0 < sqrt(tempint * tempint + tempint2 * tempint2) < 255)

                    image[i][j].rgbtRed = round(sqrt(tempint * tempint + tempint2 * tempint2));

                if (0 > sqrt(tempint * tempint + tempint2 * tempint2))
                {
                    image[i][j].rgbtRed = 0;
                }
                if (255 < sqrt(tempint * tempint + tempint2 * tempint2))
                {
                    image[i][j].rgbtRed = 255;
                }                    
            }
        }
    }
    return;
}

