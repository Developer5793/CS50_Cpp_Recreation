// Declares a dictionary's functionality
#pragma once

#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <chrono>
#include <string>
#include <vector>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Prototypes
bool check(const char *word);
unsigned int hash(const char *word);
bool load(std::vector<std::string>&dictionary);
unsigned int size(void);
template <typename T> double calculate(T start, T end);
auto timer();
bool unload(void);

