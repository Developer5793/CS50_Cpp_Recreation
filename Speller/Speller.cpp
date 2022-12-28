// Implements a spell-checker
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include "Definitions.h"
#include <chrono>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH 45

int main()

{
    // Benchmarks
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;
    //Start Timer
    auto start = Clock::now();
    // Load dictionary
    auto [loaded, dictionary] = loadwithList();
    if (!loaded) return 1;
    auto end = Clock::now();
    time_load = MeasureTime(end - start).count();
  

    FILE* text = LoadText();

    // Prepare to report misspellings
    printf("\nMISSPELLED WORDS\n\n");

    // Prepare to spell-check
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];

    // Spell-check each word in text

    char c;
    while (fread(&c, sizeof(char), 1, text))
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word[index] = c;
            index++;

            // Ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // Consume remainder of alphabetical string
                while (fread(&c, sizeof(char), 1, text) && isalpha(c));

                // Prepare for new word
                index = 0;
            }
        }

        // Ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // Consume remainder of alphanumeric string
            while (fread(&c, sizeof(char), 1, text) && isalnum(c));

            // Prepare for new word
            index = 0;
        }

        // We must have found a whole word
        else if (index > 0)
        {
            // Terminate current word
            word[index] = '\0';

            // Update counter
            words++;

            // Check word's spelling
            start = Clock::now();
            bool misspelled = !check(word, dictionary);
            end = Clock::now();
            // Update benchmark
            time_check += MeasureTime(end - start).count();
            // Print word if misspelled
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            // Prepare for next word
            index = 0;
        }
    }

    // Close text
    fclose(text);

    // Determine dictionary's size
    start = Clock::now();   
    unsigned int sn = size(dictionary);
    end = Clock::now();

    // Calculate time to determine dictionary's size
    time_size = MeasureTime(end - start).count();

    // Unload dictionary
    start = Clock::now();   
   // bool unloaded = unload();
    end = Clock::now();

    // Calculate time to unload dictionary
    time_unload = MeasureTime(end - start).count();

    // Report benchmarks
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", sn);
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN size:         %.2f\n", time_size);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n",
        time_load + time_check + time_size + time_unload);

    // Success
    return 0;
}

