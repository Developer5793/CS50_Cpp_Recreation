// Implements a dictionary's functionality

#include "Definitions.h"
#include <string>
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <ctype.h>
#include <list>
#include <vector>
#include <iterator>
#include <utility>
#include <string_view>
#include <map>


// Returns true if word is in dictionary, else false
bool check(const char* word, std::map<char, std::list<std::string>> &dictionary)
{ 
    std::string str;
    char* temp = strdup(word); // make a copy

// adjust copy to lowercase
    unsigned char* tptr = (unsigned char*)temp;
    while (*tptr) 
    {
        *tptr = tolower(*tptr);
        //Fill string with low letters
        str += *tptr;
        tptr++;
    }
    for (const auto& elem : dictionary)
    {
        if (str.front() == elem.first)
        {                   
            bool found = (std::find(dictionary[str.front()].begin(), dictionary[str.front()].end(), str) != dictionary[str.front()].end());
            {
                if (found == true)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
std::pair<bool, std::map<char, std::list<std::string>> > loadwithList() {
    std::map<char, std::list<std::string>> dictionary{};

    bool resultOK{};

    // Open File and check, if it could be opened
    if (std::ifstream ifs{ "/Users/User/Desktop/Speller/Dictionaries/large" }; ifs)
    {   
        // Fill dictionary. Read complete file and sort according to first character
        for (std::string line{}; std::getline(ifs, line);)

                // Use lower case start character for map. All words starting with that character
                dictionary[std::tolower(line.front())].push_back(line);
        resultOK = true;
    }
    else
        std::cerr << "\n\n*** Error: Could not open source file\n\n";

    // And give back the result
    return { resultOK , dictionary };
}

FILE* LoadText()
{
    char filename[100]=""; //FileName
    char fnamew[100] = ""; //Full Name with default path

    char dpath[50] = "/Users/User/Desktop/Speller/texts/"; //Default path
    char ext[5] = ".txt";

    printf("\n\nEnter Name for the New Image File (w/o path/extension):");

    if (scanf("%11s", filename) != 1) {
        fputs("Invalid input\n", stderr);
        exit(EXIT_FAILURE);
    }

    //Integrating the diff parts of filename/path
    strcpy(fnamew, dpath);
    strcat(fnamew, filename);
    strcat(fnamew, ext);
    FILE* file = fopen(fnamew, "r");


    if (file == NULL)
    {
        printf("Could not open %s.\n", fnamew);
     //   unload();
        exit;
    }

    return file;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size (std::map<char, std::list<std::string>>& dictionary)
{
    unsigned int size = 0;

    for (char l = 'a'; l <= 'z'; ++l) 
    {
        size += dictionary[l].size();
    }   
    return size;
}


