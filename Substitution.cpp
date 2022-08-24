
//A programm to encrypt a message for any given alphabetical input key


#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <cmath>
#include <string>


using namespace std;


char Alphabet[26] = { 'A', 'B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
char smallAlphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
char Signs[6] = { ' ', ',', '.', '?', '#' ,'!' };

const int INPUTSIZE = 2000;
const int KEYINT = 1000;
char input1[KEYINT];
char InputMessage[INPUTSIZE];
char Output1[26];
char Output2[26];
char Output3[6];
int main()
{
    while (true) {
        char CodeInput;
        int numbLetters;
        int i = 0, k = 0, z = 0, g = 0, a = 0;
        int keylenght;


        //Catch Input-Key
    noobi:
        std::cout << "Please enter the 26-Digit Code: " << endl;
        cin.getline(input1, KEYINT);

//Check for correct lenght
        keylenght = 0;
        for (keylenght = 0; input1[keylenght] != '\0'; keylenght++);



        if (keylenght == 26)
        {
            int comparator;

            //Check if key only contains letters
            for (k = 0; k < 26; k++) {
                for (comparator = 0; comparator < 26; comparator++) {
                    if (input1[k] == Alphabet[comparator] || input1[k] == smallAlphabet[comparator]) {
                        break;
                    }
                }
                if (input1[k] == Alphabet[comparator] || input1[k] == smallAlphabet[comparator]) {
                }
                else if (input1[k] != Alphabet[comparator] || input1[k] != smallAlphabet[comparator]) {
                    cout << "Please use letters only." << endl;
                    goto noobi;
                }
            }

            //Catch Input Message
            std::cout << "Please enter the message you want to encrypt: ";
            cin.getline(InputMessage, INPUTSIZE);
            cout << endl;



            cout << "The Message is: ";

            //Convert the Inputmessage with help of the input key to an Output Message
            for (z = 0; z <= INPUTSIZE; z++) {
                for (g = 0; g < 26; g++) {
                    if (Alphabet[g] == InputMessage[z]) {
                        Output1[g] = (toupper(input1[g]));
                        cout << Output1[g];
                    }
                }
                for (a = 0; a < 26; a++) {
                    if (InputMessage[z] == smallAlphabet[a]) {
                        Output2[a] = (tolower(input1[a]));
                        cout << Output2[a];
                    }
                }
                for (int q = 0; q < 6; q++) {
                    if (InputMessage[z] == Signs[q]) {
                        Output3[q] = Signs[q];
                        cout << Output3[q];
                    }
                }

            }
            cout << endl;
            cout << endl;

        }
        else if (keylenght != 26) { cout << "Please use 26 digits and letters only" << endl; }
    }
    return 0;
}