// Implements a dictionary's functionality

#include <stdbool.h>
#include "Definitions.h"
#include <fstream>
#include <string>
#include <chrono>
#include <vector>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load (std::vector<std::string> &dictionary)
{
    FILE* fp = fopen("dictionaries/small", "r"); 
    if (fp == NULL)
            return false;

     char* line = NULL;
    size_t len = 0;
    while ((getline(&line, &len, fp)) != -1) 
    {
         std::string temp << line;
         dictionary.push_back(temp);

    }
    fclose(fp);
    if (line)
        free(line);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}


//Takes time
auto timer()
{
    auto time = std::chrono::high_resolution_clock::now();
    return time;
}

//Returns number of milliseconds between start and end
template <typename T> double calculate(T start, T end)
{
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
    return elapsed_time_ms;
}