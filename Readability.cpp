// Programm that tries categorize the difficulty of texts with a given formula

#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <cmath>
#include <string>

using namespace std;


int wordCount(char* str);
int letterCount(char* str);
int sentenceCount(char* str);
const int SIZE = 2000;

int main()
    {
   
        char input[SIZE];
        int numWords = 0;
        float numLetters = 0;
        float numSentences = 77;
        float index;
        float L = 0;
        float S = 0;

        //Input functions

        cout << "Enter a text you like to be categorized: " << endl;
        cin.getline(input, SIZE);

        numSentences = sentenceCount(input);
        cout << "The number of sentences in your text is: " << numSentences << endl;

        numWords = wordCount(input);
        cout << "The number of words in your text is: " << numWords << endl;

        numLetters = letterCount(input);
        cout << "The number of letters in your text is: " << numLetters << endl;

        //Develop categorization function

        L = numLetters * 100 / numWords;
        S = numSentences * 100 / numWords;


        index = 0.0588 * L - 0.296 * S - 15.8;
        index = round(index);

        if (index <= 1) {
            cout << "The Grade is: 1" << endl;
        }
        else if (index >= 16) {
            cout << "The Grade is: 16+ " << endl;
        }
        else {
            cout << "The Grade is: " << index << endl;
        }



        return 0;
    }

//count words, letters, sentences

int wordCount(char* str) {
    float numWords = 0;

    while (*str) {
        if (*str == ' ') {
            numWords++;
        }
        str++;
    }
    return numWords + 1;
}

int letterCount(char* str) {
    float numLetters = 0;

    while (*str) {
        if (*str != ' ' &&  *str != '.' && *str != '?' && *str != '!' && *str != '?' && *str != ';' && *str != ':'&& *str !='\'' && *str != ',')
        {
            numLetters++;
        }
        
            str++;
        
   }
    return numLetters;
}
int sentenceCount(char* str) {
    float numSentences = 0;

    while (*str) {
        if (*str == '.' || *str == '!' || *str == '?'|| *str == ':') {
            numSentences++;
        }
        str++;
    }
    return numSentences;
}


