//Tideman voting algorithm // 
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

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
int pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(string name, int rank);
void record_preferences(int ranks[], string namesarr[]);
void add_pairs(int ranks[], string namesarr[]);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

const int len = 1000;
char inputnames[len];
int counter;
int voter_count;

string namesarr[9];
string name;
int ranks[9];
int candidaterank;

//Array with max possibilities of one winning over the other// Candidate 1 can win 8 times over the other ones etc.
string WinnerandLoserPairs[100];

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
    for (int i = 0; i < counter; i++)
    {
        iss >> token;
        if (iss) {
            candidates[i] = token;
            cout << candidates[i] << endl;
        }
    }
  
    // Clear graph of locked in pairs
    for (int i = 0; i < counter; i++)
    {
        for (int j = 0; j < counter; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;

    cout << "Type in number of voters: ";
   
    cin >> voter_count;
    cout << endl;

    cout << "Please type in the candidates names and rank the candidates from first to last candidade. \n";
    // Query each voter for vote
    for (int i = 0; i < voter_count; i++)
    {   // Query for each name and rank //Fill arrays to structure rankings
        for (int j = 0; j < counter; j++)
        {
            //ONE LINE PLZ
            cout << "Name: ";
            cin >> name;
            cout << "Rank: ";
            cin >> candidaterank;
            cout << endl;

            //Compare each input name with predefined candidate array and if it fits to candidate array & ranks 1-9 fill in the user inputs in arrays
            //DEBUG here if someone ranks one person one the same rank two times/writes the same name twice for the same rank
            if (!vote(name, candidaterank))
            {
                printf("Invalid vote. Vote again please \n");
            }

            else if (vote(name, candidaterank))
            {
                namesarr[j] = name;
                ranks[j] = candidaterank;
            }

        }
        record_preferences(ranks, namesarr);
        printf("\n");

        add_pairs(ranks, namesarr);
    }

    
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

//Check for valid vote 
bool vote(string name, int candidaterank)
{
    for (int z = 0; z < counter; z++)
    {
        if (strcmp(candidates[z].c_str(), name.c_str()) == 0 && 0 < candidaterank && candidaterank <= counter)
        {
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks and rank the candidates from first to last
void record_preferences(int ranks[], string namesarr[])
{
    for (int q = 0; q < counter; q++)
    {
        //Sorting the array of voted candidates first by second, second by third, third by fourth...
        for (int b = 0; b < counter; b++)
        {
            if ( ranks[b] > ranks[b + 1] && ranks[b+1] != 0 && ranks [b]!=0)
            {
                swap(ranks[b], ranks[b + 1]);
                swap(namesarr[b], namesarr[b + 1]);
            }
        }      
    }
    for(int d=0; d<counter; d++)
    {
        cout <<"Name: " << namesarr[d] << endl;
        cout <<"Rank: " << ranks[d] << endl;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(int ranks[], string namesarr[])
{
        for (int winnercounter = 0; winnercounter < counter; winnercounter++)
        {
            for (int losercounter = winnercounter+1; losercounter < counter; losercounter++)
            {
                 if (namesarr[winnercounter] != namesarr[losercounter])
                 {
                     WinnerandLoserPairs[0] = namesarr[winnercounter];
                     WinnerandLoserPairs[1] = namesarr[losercounter];
                     cout << "Winner: " << WinnerandLoserPairs[0] << endl;
                     cout << "Loser: " << WinnerandLoserPairs[1] << endl;
                     cout << endl;
                 }
            }
        }
   return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}