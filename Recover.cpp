// Recover.cpp : Program to recover deleted JPGs from memory card
//
#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>
#include <string>

int main()
{   
    //Open files
    std::ifstream myfile("card.raw", std::ios::binary);
    std::ofstream mypic;
    int picnumber = 0;

    if (myfile.is_open())
    {
        std::cout << "File is ready to use\n";
    }
    // Copy all data from file into buffer
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(myfile), {});
    
    if (std::istreambuf_iterator<char>(myfile) == std::istreambuf_iterator<char>()) 
    {
        std::cout << "File sucessfully read\n";
        myfile.close();
    }
  
    //Search in buffer
    for (int index = 0; index < buffer.size(); index = index + 512)
    {
        //Find four right ordered bytes
        if (buffer[index] == 0xff && buffer[index + 1] == 0xd8 && buffer[index + 2] == 0xff && (buffer[index + 3] & 0xf0) == 0xe0)
        {            
            std::cout << "Values found\n";
          
            //Numerize files from 000-049
            std::string stringpic = std::to_string(picnumber);
            size_t n = 3;
            int precision = n - std::min(n, stringpic.size());
            std::string s = std::string(precision, '0').append(stringpic);
            
            mypic.open(s+".jpg",std::ios::binary);
           
            for (int it = index; it < buffer.size(); it++)
            {
                mypic << buffer[it];
                if (buffer[it] == 0xff && buffer[it + 1] == 0xd8 && buffer[it + 2] == 0xff && (buffer[it + 3] & 0xf0) == 0xe0&& it!=index)
                {
                    mypic.close();
                    picnumber++;
                    break;
                }
            }
        }
    }  
}
