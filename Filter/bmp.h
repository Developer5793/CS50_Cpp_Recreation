 //related data types based on Microsoft's own
#pragma once

#include <iostream>
#include "bmp.h"


   typydef uint8_t  BYTE;
   typydef uint32_t DWORD;
   typydef int32_t  LONG;
   typydef uint16_t WORD;

#pragma pack (1)

    typedef struct BITMAPFILEHEADER
    {
        WORD  bfType;
        DWORD bfSize;
        WORD  bfReserved1;
        WORD  bfReserved2;
        DWORD bfOffBits;
    };
 
    typedef struct BITMAPINFOHEADER {
        DWORD biSize;
        LONG  biWidth;
        LONG  biHeight;
        WORD  biPlanes;
        WORD  biBitCount;
        DWORD biCompression;
        DWORD biSizeImage;
        LONG  biXPelsPerMeter;
        LONG  biYPelsPerMeter;
        DWORD biClrUsed;
        DWORD biClrImportant;
    };

    
    typedef struct RGBTRIPLE {
        BYTE rgbtBlue;
        BYTE rgbtGreen;
        BYTE rgbtRed;
    };

