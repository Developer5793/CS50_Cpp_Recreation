#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "FileHeaders.h"
//#include "helpers.h"
#include <fstream>
#include <iterator>
#include <algorithm>


char PickAFilter();

int main()
{
    //Choose Filter
    char userinput = PickAFilter();

    //Define Input/Output stream 
    std::ifstream();

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
         std::cout << "The filesize is: " << position<<" Bytes\n";


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
                     std::cout << "Current position in stream is: "<<position<<"th Byte\n";

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
    int width = Infos[5].biWidth;

    std::cout << height << "\n";
    std::cout << width << "\n";

    /*test 1
    std::vector<unsigned char>prototype(std::istreambuf_iterator<char>(infile), {});
    std::cout << prototype[232323]<<"\n";

    std::cout << prototype[232323] << "\n";
    std::cout << prototype[342323] << "\n";
    std::cout << prototype[642323] << "\n";
    std::cout << prototype[541345] << "\n";
    std::cout << prototype[413453] << "\n";

    std::cout << "-Vector end-\n";
    */


    //Read image into buffer to edit it
       infile.seekg(position,std::ios::end);
        position  = infile.tellg();
         infile.seekg(54, std::ios::beg);
           int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;
            std::cout << position<<"\n";

            std::vector<unsigned char>buffer(position);
                infile.read((char*)&buffer[0], position);
                    
        int bufferlenght = 0;
        std::vector<std::vector<RGBTRIPLE>> image(height, std::vector<RGBTRIPLE>(width));
            for(int z=0; z<height; z++)
            {
                for (int i = 0; i < width; i++)
                {
                    image[z][i].rgbtBlue = buffer[bufferlenght++];
                        image[z][i].rgbtGreen = buffer[bufferlenght++];
                             image[z][i].rgbtRed = buffer[bufferlenght++];

                }
            }

            std::cout<<"Bufferlenght: " << bufferlenght << "\n";
            /*test 2
            std::cout << buffer[345733]<<"\n";
            std::cout << buffer[232323] << "\n";
            std::cout << buffer[342323] << "\n";
            std::cout << buffer[642323] << "\n";
            std::cout << buffer[541345] << "\n";
            std::cout << buffer[413453] << "\n";
            std::cout << "-Buffer end-\n";
            */


           // Test3
            std::cout << image[200][340].rgbtBlue << "\n";
            std::cout << image[200][534].rgbtGreen << "\n\n";

            std::cout << image[200][144].rgbtRed << "\n";
            std::cout << image[200][144].rgbtGreen << "\n";
            std::cout << image[200][144].rgbtBlue << "\n\n";

            std::cout << image[350][255].rgbtGreen << "\n";
            std::cout << image[321][255].rgbtBlue << "\n";
            std::cout << image[42][455].rgbtGreen << "\n";
            std::cout << image[112][245].rgbtBlue << "\n";
            std::cout << image[234][135].rgbtRed << "\n";
            





     // Iterate over infile's
            // for (int i = 0; i < height; i++)
            // {
                 // Read row into pixel array

                 // Skip over padding
            // }



    //?//


    /*
     // Filter image
     switch (filter)
     {
         // Blur
     case 'b':
         blur(height, width, image);
         break;

         // Edges
     case 'e':
         edges(height, width, image);
         break;

         // Grayscale
     case 'g':
         grayscale(height, width, image);
         break;

         // Reflect
     case 'r':
         reflect(height, width, image);
         break;
     }

     // Write outfile's BITMAPFILEHEADER
     fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

     // Write outfile's BITMAPINFOHEADER
     fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

     // Write new pixels to outfile
     for (int i = 0; i < height; i++)
     {
         // Write row to outfile
         fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

         // Write padding at end of row
         for (int k = 0; k < padding; k++)
         {
             fputc(0x00, outptr);
         }
     }

     // Free memory for image
     free(image);

     // Close files
     fclose(inptr);
     fclose(outptr);
     return 0;
 }
 */
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