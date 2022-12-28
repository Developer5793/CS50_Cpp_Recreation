#pragma once

#include <vector>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <map>

// Prototypes
bool check (const char* word, std::map<char, std::list<std::string>>& dictionary);
std::pair<bool, std::map<char, std::list<std::string>> > loadwithList();
unsigned int size (std::map<char, std::list<std::string>> &dictionary);
FILE* LoadText();

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::duration<double, std::milli> MeasureTime;


