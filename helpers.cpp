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
void grayscale(int height, int width,  std::vector<std::vector<RGBTRIPLE>>&image)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtGreen = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtRed = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {      
            if (i - 1 >= 0 && j - 1 >= 0 && j + 1 < width && i + 1 < height)
            {
                image[i][j].rgbtBlue = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                    image[i + 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9;

                image[i][j].rgbtGreen = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                    image[i + 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9;

                image[i][j].rgbtRed = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                    image[i + 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9;
            }
        }
    }
    return;
}

// Detect edges
/*
void edges(int height, int width, std::vector<std::vector<RGBTRIPLE>>& image)

    {
        std::vector<std::vector<RGBTRIPLE>>temp = image;
        std::vector<std::vector<RGBTRIPLE>>temp2 = image;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (i - 1 >= 0 && j - 1 >= 0 && j + 1 < width && i + 1 < height)
                {


                }
            }
        } 
    }
*/











// Detect edges
void edges(int height, int width, std::vector<std::vector<RGBTRIPLE>> &image)
{
    std::vector<std::vector<RGBTRIPLE>>temp = image;
    std::vector<std::vector<RGBTRIPLE>>temp2 = image;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i - 1 >= 0 && j - 1 >= 0 && j + 1 < width && i + 1 < height)
            {
                //Mess and not working 
                

                     //Gx-Blue                                   
                temp[i][j].rgbtBlue = fmin(round(temp[i][j].rgbtBlue * 0 + temp[i][j + 1].rgbtBlue * 2 + temp[i][j - 1].rgbtBlue * (-2) + temp[i - 1][j].rgbtBlue * 0 +
                    temp[i + 1][j].rgbtBlue * 0 + temp[i - 1][j - 1].rgbtBlue * (-1) + temp[i - 1][j + 1].rgbtBlue * 1 + temp[i + 1][j - 1].rgbtBlue * (-1) + temp[i + 1][j + 1].rgbtBlue * 1), 255);
                //Gy-Blue
                temp2[i][j].rgbtBlue = fmin(round(temp2[i][j].rgbtBlue * 0 + temp2[i][j + 1].rgbtBlue * 0 + temp2[i][j - 1].rgbtBlue * (0) + temp2[i - 1][j].rgbtBlue * (-2) +
                    temp2[i + 1][j].rgbtBlue * 2 + temp2[i - 1][j - 1].rgbtBlue * (-1) + temp2[i - 1][j + 1].rgbtBlue * (-1) + temp2[i + 1][j - 1].rgbtBlue * (1) + temp2[i + 1][j + 1].rgbtBlue * 1),255);

                image[i][j].rgbtBlue = fmin(round(sqrt(temp[i][j].rgbtBlue * temp[i][j].rgbtBlue + temp2[i][j].rgbtBlue * temp2[i][j].rgbtBlue)), 255);


                //Gx-Green
                temp[i][j].rgbtGreen = fmin(round(temp[i][j].rgbtGreen * 0 + temp[i][j + 1].rgbtGreen * 2 + temp[i][j - 1].rgbtGreen * (-2) + temp[i - 1][j].rgbtGreen * 0 +
                    temp[i + 1][j].rgbtGreen * 0 + temp[i - 1][j - 1].rgbtGreen * (-1) + temp[i - 1][j + 1].rgbtGreen * 1 + temp[i + 1][j - 1].rgbtGreen * (-1) + temp[i + 1][j + 1].rgbtGreen * 1),255);
                //Gy-green
                temp2[i][j].rgbtGreen = fmin(round(temp2[i][j].rgbtGreen * 0 + temp2[i][j + 1].rgbtGreen * 0 + temp2[i][j - 1].rgbtGreen * (0) + temp2[i - 1][j].rgbtGreen * (-2) +
                    temp2[i + 1][j].rgbtGreen * 2 + temp2[i - 1][j - 1].rgbtGreen * (-1) + temp2[i - 1][j + 1].rgbtGreen * (-1) + temp2[i + 1][j - 1].rgbtGreen * (1) + temp2[i + 1][j + 1].rgbtGreen * 1),255);

                image[i][j].rgbtGreen = fmin(round(sqrt(temp[i][j].rgbtGreen * temp[i][j].rgbtGreen + temp2[i][j].rgbtGreen * temp2[i][j].rgbtGreen)), 255);


                //Gx-Green
                temp[i][j].rgbtRed = fmin(round(temp[i][j].rgbtRed * 0 + temp[i][j + 1].rgbtRed * 2 + temp[i][j - 1].rgbtRed * (-2) + temp[i - 1][j].rgbtRed * 0 +
                    temp[i + 1][j].rgbtRed * 0 + temp[i - 1][j - 1].rgbtRed * (-1) + temp[i - 1][j + 1].rgbtRed * 1 + temp[i + 1][j - 1].rgbtRed * (-1) + temp[i + 1][j + 1].rgbtRed * 1),255);
                //Gy-green
                temp2[i][j].rgbtRed = fmin(round(temp2[i][j].rgbtRed * 0 + temp2[i][j + 1].rgbtRed * 0 + temp2[i][j - 1].rgbtRed * (0) + temp2[i - 1][j].rgbtRed * (-2) +
                    temp2[i + 1][j].rgbtRed * 2 + temp2[i - 1][j - 1].rgbtRed * (-1) + temp2[i - 1][j + 1].rgbtRed * (-1) + temp2[i + 1][j - 1].rgbtRed * (1) + temp2[i + 1][j + 1].rgbtRed * 1),255);

                image[i][j].rgbtRed = fmin(round(sqrt(temp[i][j].rgbtRed * temp[i][j].rgbtRed + temp2[i][j].rgbtRed * temp2[i][j].rgbtRed)), 255);
            
            }
        }
    }
    return;
}
