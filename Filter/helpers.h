#pragma once

#include "FileHeaders.h"
#include <vector>

// Convert image to grayscale
void grayscale(int height, int width, std::vector<std::vector<RGBTRIPLE>> &image);


// Reflect image horizontally
void reflect(int height, int width, std::vector<std::vector<RGBTRIPLE>> &image);

// Detect edges
void edges(int height, int width, std::vector<std::vector<RGBTRIPLE>> &image);

// Blur image
void blur(int height, int width, std::vector<std::vector<RGBTRIPLE>>& image);

