//Voting algorithm





#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <algorithm>

using namespace std;

const int len = 1000;
char inputnames[len];

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}candidate;



// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int counter;

int main()
{
    int z = 0;

    cout << "Type in the Candidates names and press enter please: ";


    cin.getline(inputnames, len);
    string stringstream(inputnames);
    istringstream iss(stringstream);
    string token;

    char LastCharacter = stringstream.back();

    //Enable input of candidates with any number of spaces in between before or after and count number of candidates then 

    if (LastCharacter == ' ') {
        counter = 0;
        for (int z = 0; z < len; z++) {
            if (inputnames[z] >= 'a' && inputnames[z] <= 'z' && inputnames[z + 1] == ' ' || inputnames[z] >= 'A' && inputnames[z] <= 'Z' && inputnames[z] == ' ')
            {
                counter++;
            }
            cout << inputnames[z];
        }
    }

    else if (LastCharacter != ' ') {
        counter = 1;
        for (int z = 0; z < len; z++) {
            if (inputnames[z] >= 'a' && inputnames[z] <= 'z' && inputnames[z + 1] == ' ' || inputnames[z] >= 'A' && inputnames[z] <= 'Z' && inputnames[z] == ' ')
            {
                counter++;
            }
            cout << inputnames[z];
        }
    }
    cout << endl;
    cout << counter << endl;

    if (0 < counter && counter < MAX) {
        cout << "Number of Candidates: " << counter << endl;
    }

    // Check for invalid usage
    else if (counter == 0)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    if (counter > MAX)
    {
        cout << "Maximum number of candidates is: " << MAX << endl;
        return 2;
    }

    // Populate array of candidates with istringstream 

    for (int i = 0; i < counter; i++)
    {
        iss >> token;
        if (iss) {
            candidates[i].name = token;
            candidates[i].votes = 0;
            cout << candidates[i].name << endl;
        }
    }
    int voter_count;
    cout << "Type in number of voters: ";
    cin >> voter_count;

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name;
        cout << "Vote: ";
        cin >> name;

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}


// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < counter; i++)
    {
        if (strcmp(candidates[i].name.c_str(), name.c_str()) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //Sorting the input array one by one. First by second, first by third....
    for (int i = 0; i < counter; i++)
    {
        for ( int n=1 ; n<counter; n++)
        {
            if (candidates[i + n].votes > candidates[i].votes)
            {
                swap(candidates[i + n].votes, candidates[i].votes);
                swap(candidates[i + n].name, candidates[i].name);
            }

        }
        cout << candidates[i].name;
        cout << ": ";
        cout << candidates[i].votes << endl;


    }





}

