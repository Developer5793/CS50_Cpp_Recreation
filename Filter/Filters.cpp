#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <stdint.h>
#include "helpers.h"

char PickAFilter();


int main()

{
    //Choose Filter
    char userinput = PickAFilter();

    //Define Input/Output stream 
    std::ifstream();
    std::ofstream();
    std::string filename;
    std::cout << "Enter the filename please:\n";
    std::cin >> filename;

    //Open input file
    std::ifstream infile("/Users/User/Desktop/HPictures/" + filename + ".bmp", std::ios::in | std::ios::binary | std::ios::ate);

    if (infile.is_open())
    {
        std::cout << "success\n";
    }

    if (!(infile.is_open()))
    {
        std::cout << "Failed to open file\n";
    }

    std::streampos position;
    position = infile.tellg();
   int filesize = position;
    std::cout << "The filesize is: " << filesize << " Bytes\n";

    // Store Fileheader's 
    BITMAPFILEHEADER temp;
    std::vector<BITMAPFILEHEADER>Header;
    infile.seekg(0, infile.beg);
    infile.read((char*)&temp, sizeof(BITMAPFILEHEADER));
    Header.assign(5, temp);

    BITMAPINFOHEADER temp2;
    std::vector<BITMAPINFOHEADER>Infos;
    infile.seekg(0 + sizeof(BITMAPFILEHEADER), infile.beg);
    infile.read((char*)&temp2, sizeof(BITMAPINFOHEADER));
    Infos.assign(11, temp2);
    position = infile.tellg();
    std::cout << "Current position in stream is: " << position << "th Byte\n";

    //Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (Header[0].bfType != 0x4d42 || Header[0].bfOffBits != 54 || temp2.biSize != 40 ||
        temp2.biBitCount != 24 || temp2.biCompression != 0)
    {
        infile.close();
        std::cout << "Unsupported file format.\n";
        return 6;
    }

    // Get image's dimensions
   int height = -1 * (Infos[2].biHeight);
 int   width = Infos[5].biWidth;

    std::cout<<"height is: " << height << "\n";
    std::cout <<"width is: "<< width << "\n";


    //Read image into buffer to edit it
    infile.seekg(position, std::ios::end);
    position = infile.tellg();
    infile.seekg(54, std::ios::beg);
    std::cout << position << "\n";

    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;
    std::cout << padding;
    std::vector<std::vector<RGBTRIPLE>>image(height, std::vector<RGBTRIPLE>(width));
    for (int z = 0; z < height; z++)
    {
        infile.read((char*)&image[z][0], width * sizeof(RGBTRIPLE));
        //Skip Padding?
      // infile.seekg(std::ios::cur + padding, std::ios::cur);
    }
    infile.close();


    // Filter image
    switch (userinput)
    {
        // Blur
    case 'b':
        blur(height, width, image);
        break;

        // Edges
    case 'e':
        edges(height, width, image);
        break;

        //Grayscale
    case 'g':
        grayscale(height, width, image);
        break;

        //Reflect
    case 'r':
        reflect(height, width, image);
        break;
    }

    
    std::cout << "Enter the filename please: ";
    std::string outfile;
    std::cin >> outfile;

    std::ofstream mypicture("/Users/User/Desktop/HPictures/" + outfile + ".bmp", std::ios::binary | std::ios::out | std::ios::beg);
    if (!(mypicture.is_open()))
    {
        std::cout << "\nCould not open file\n";

    }


    //Write to outputfile
    mypicture.write((char*)&Header[0], sizeof(BITMAPFILEHEADER));
    mypicture.write((char*)&Infos[0], sizeof(BITMAPINFOHEADER));

    for (int z = 0; z < height; z++)
    {
        mypicture.write((char*)&image[z][0], width * sizeof(RGBTRIPLE));
        //Skip Padding?
     //   mypicture.seekp(std::ios::cur + padding, std::ios::cur);
    }

    mypicture.close();

      
         return 0;
         
}
char PickAFilter()

{
    std::string userinput;

    // Define allowable filters
    char filter[5] = "begr";
    char* str = &filter[0];
    int breakthisloop = 0;

    // Get filter flag and check validity
    while (breakthisloop == 0)
    {
        std::cout << "Type in Filter b,e,g or r please\n";
        std::getline(std::cin, userinput);

        if (userinput.size() == 1)
        {
            while (*str)
            {
                if (userinput[0] == *str)
                {
                    breakthisloop = 1;
                    break;
                }
                str++;
                if (*str == '\0')
                {
                    std::cout << "Invalid filter.\n";
                    str = &filter[0];
                    break;
                }
            }
        }
        if (userinput.size() > 1)
        {
            std::cout << "Only one filter allowed.\n";
        }
    }
    str = NULL;
    return userinput[0];
}


