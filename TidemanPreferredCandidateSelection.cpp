
//Tideman voting algorithm // 
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
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
    string PairstoLock;
    int voternumber;
}
PairstoCheck;

// Array of Pairs to check for lock
PairstoCheck Pairstocheck[50][50];


string candidates[MAX];

int pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(string name, int rank);
void record_preferences(int ranks[], string namesarr[]);
void add_pairs(int& winnerslosersarrlenght);
void sort_pairs(int& lol);
void lock_pairs(int& winners, int& losers);
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
string WinnersandLosersarr[100][100];
string newWinnersLosersarr[100][100];
string Locked_Pairs[50][50];


int Rankingsarray[50];
int Rankingsarray2[50][50];


int Winnercounter[50];
int Sortedwinsarray[50];

int winnerslosersarrlenght = 0;
int lol = 0;

int winnerslrsarrlenghtres = 0;

int Electionarray[50][50];
int winners, losers;



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

        add_pairs(winnerslosersarrlenght);
        cout << winnerslosersarrlenght << endl;
    }
    cout << winnerslosersarrlenght << endl;
    //Sorting to fix
    for (int pp = 0; pp < winnerslosersarrlenght; pp++)
    {
        cout << WinnersandLosersarr[pp][0];
        cout << "  " << WinnersandLosersarr[pp][1];
        cout << endl;
    }
    cout << endl;
    sort_pairs(lol);
    lock_pairs(winners, losers);
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
            if (ranks[b] > ranks[b + 1] && ranks[b + 1] != 0 && ranks[b] != 0)
            {
                swap(ranks[b], ranks[b + 1]);
                swap(namesarr[b], namesarr[b + 1]);
            }
        }
    }
    for (int d = 0; d < counter; d++)
    {
        cout << "Name: " << namesarr[d] << endl;
        cout << "Rank: " << ranks[d] << endl;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(int& winnerslosersarrlenght)
{
    for (int winnercounter = 0; winnercounter < counter; winnercounter++)
    {
        for (int losercounter = winnercounter + 1; losercounter < counter; losercounter++)
        {
            if (namesarr[winnercounter] != namesarr[losercounter])
            {
                WinnerandLoserPairs[0] = namesarr[winnercounter];
                WinnerandLoserPairs[1] = namesarr[losercounter];
                cout << "Winner: " << WinnerandLoserPairs[0] << endl;
                cout << "Loser: " << WinnerandLoserPairs[1] << endl;
                cout << endl;
                //Record Winner and Loser pairs in a 2-dimensional array
                for (int p = 1; p < 2; p++)
                {
                    WinnersandLosersarr[winnerslosersarrlenght][0] = WinnerandLoserPairs[0];
                    WinnersandLosersarr[winnerslosersarrlenght][1] = WinnerandLoserPairs[1];
                    winnerslosersarrlenght++;
                }
            }
        }
    }
    return;
}

// Sort pairs by winners
void sort_pairs(int& lol)
{
    for (int g = 0; g < winnerslosersarrlenght; g++)
    {
        for (int q = g + 1; q < winnerslosersarrlenght; q++)
        {
            if (WinnersandLosersarr[g][0] != WinnersandLosersarr[q][0])
            {
                for (int f = q + 1; f < winnerslosersarrlenght; f++)
                {
                    if (WinnersandLosersarr[f][0] == WinnersandLosersarr[g][0])
                    {
                        swap(WinnersandLosersarr[f][0], WinnersandLosersarr[q][0]);
                        swap(WinnersandLosersarr[f][1], WinnersandLosersarr[q][1]);
                        f = winnerslosersarrlenght - 1;
                    }
                }
            }
        }
    }
    for (int pp = 0; pp < winnerslosersarrlenght; pp++)
    {
        cout << WinnersandLosersarr[pp][0];
        cout << WinnersandLosersarr[pp][1];
        cout << endl;
    }
    cout << endl;

    //Sort pairs by amount of times one candidate won over the other
    for (int g = 0; g < winnerslosersarrlenght; g++)
    {
        for (int q = g + 1; q < winnerslosersarrlenght; q++)
        {
            if (WinnersandLosersarr[g][0] == WinnersandLosersarr[q][0] && WinnersandLosersarr[g][1] != WinnersandLosersarr[q][1])
            {
                for (int j = q + 1; j < winnerslosersarrlenght; j++)
                {
                    if (WinnersandLosersarr[g][0] == WinnersandLosersarr[j][0] && WinnersandLosersarr[g][1] == WinnersandLosersarr[j][1])
                    {
                        swap(WinnersandLosersarr[q][0], WinnersandLosersarr[j][0]);
                        swap(WinnersandLosersarr[q][1], WinnersandLosersarr[j][1]);
                        j = winnerslosersarrlenght - 1;
                    }
                }
            }
        }
    }
    for (int pp = 0; pp < winnerslosersarrlenght; pp++)
    {
        cout << WinnersandLosersarr[pp][0];
        cout << WinnersandLosersarr[pp][1];
        cout << endl;
    }
    cout << endl;




    //Structure Amount of Wins from one candidate over the other 
    for (int g = 0; g < winnerslosersarrlenght; g++)
    {
        Rankingsarray[lol]++;

        if (WinnersandLosersarr[g][1] != WinnersandLosersarr[g + 1][1] || WinnersandLosersarr[g][1] == WinnersandLosersarr[g + 1][1] && WinnersandLosersarr[g][0] != WinnersandLosersarr[g + 1][0])
        {
            lol++;
        }
    }

    for (int h = 0; h < lol; h++)
    {
        cout << Rankingsarray[h] << endl;
    }
    cout << endl;

    //Sort Rankingsarray to compare it with the Winnersandlosersarray next to sort by strongest win of one candidate over the other to form a new array
    for (int i = 0; i < 20; i++)
    {
        for (int k = 0; k < 25; k++)
        {
            if (Rankingsarray[k] <= Rankingsarray[k + 1] && Rankingsarray[k + 1] != 0 && Rankingsarray[k] != 0)
            {
                swap(Rankingsarray[k], Rankingsarray[k + 1]);
            }
        }
    }

    for (int h = 0; h < lol; h++)
    {
        cout << Rankingsarray[h] << endl;
    }
    cout << endl;

    int q = 0;
    int r = 0;
    int t = 0;


    //Count through the Winners and losers array to find the right quantity of wins to comply with the sorted Rankingsarray
    //Then put pairs in two advanced rows, overwrite the arrays with empty strings to deny multiple usage and then put it back in the old array

    for (int i = 0; i <= 50; i++)
    {
        for (int z = 0; z < winnerslosersarrlenght; z++)
        {
            r++;
            if (r == Rankingsarray[t] && WinnersandLosersarr[z][0] != "" && WinnersandLosersarr[z][1] != "")
            {
                for (int s1 = 0; s1 < Rankingsarray[t]; s1++)
                {
                    WinnersandLosersarr[q][2] = WinnersandLosersarr[z][0];
                    WinnersandLosersarr[q][3] = WinnersandLosersarr[z][1];
                    q++;
                }
                for (int s2 = 0, s3 = z; s2 < Rankingsarray[t]; s2++)
                {
                    WinnersandLosersarr[s3][0] = "";
                    WinnersandLosersarr[s3][1] = "";
                    if (s3 > 0)
                    {
                        s3--;
                    }
                    else if (s3 == 0)
                    {
                        s3 = 0;
                    }
                }
                t++;
            }
            if (WinnersandLosersarr[z][1] != WinnersandLosersarr[z + 1][1] || WinnersandLosersarr[z][1] == WinnersandLosersarr[z + 1][1] && WinnersandLosersarr[z][0] != WinnersandLosersarr[z + 1][0])
            {
                r = 0;
            }

        }
    }

    cout << endl;

    for (int h = 0; h < winnerslosersarrlenght; h++)
    {
        WinnersandLosersarr[h][0] = WinnersandLosersarr[h][2];
        cout << WinnersandLosersarr[h][2];
        cout << " ";
        WinnersandLosersarr[h][1] = WinnersandLosersarr[h][3];
        cout << WinnersandLosersarr[h][3];
        cout << endl;
    }
    cout << endl;

    return;
}




// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(int& winners, int& losers)
{

    int j = 0;

    for (int i = 0; i < lol; i++)
    {
        Rankingsarray2[i][0] = Rankingsarray[i];
    }


    //Print Scores & Ignore all pairs when the opposite pair is found above
    for (int c = 0; c < winnerslosersarrlenght; c++)
    {
        if (WinnersandLosersarr[c][1] != WinnersandLosersarr[c + 1][1] || WinnersandLosersarr[c][1] == WinnersandLosersarr[c + 1][1] && WinnersandLosersarr[c][0] != WinnersandLosersarr[c + 1][0])
        {
            for (int d = c + 1; d < winnerslosersarrlenght; d++)
            {
                if (WinnersandLosersarr[c][0] == WinnersandLosersarr[d][1] && WinnersandLosersarr[c][1] == WinnersandLosersarr[d][0])
                {
                    Rankingsarray2[j][1]++;
                }
            }
            j++;
        }
    }
    for (int k = 0; k < lol; k++)
    {
        cout << Rankingsarray2[k][0];
        cout << " ";
        cout << Rankingsarray2[k][1];
        cout << endl;
    }
    cout << endl;

    for (int u = 0; u < lol; u++)
    {
        Rankingsarray2[u][2] = Rankingsarray2[u][0] - Rankingsarray2[u][1];
        Rankingsarray2[u][3] = Rankingsarray2[u][1] - Rankingsarray2[u][0];
    }

    for (int k = 0; k < lol; k++)
    {
        cout << Rankingsarray2[k][2];
        cout << endl;
    }

    cout << endl;

    for (int k = 0; k < lol; k++)
    {
        cout << Rankingsarray2[k][3];
        cout << endl;
    }
    cout << endl;

    int w = 0;
    int voices = 0;



    for (int votes = 0; votes < lol; votes++)
    {
        Rankingsarray2[votes][4] = Rankingsarray2[votes][2];
        w++;
        voices++;
    }
    for (int votes = 0; votes < lol; votes++)
    {
        Rankingsarray2[w][4] = Rankingsarray2[votes][3];
        voices++;
        w++;
    }


    for (int k = 0; k < voices; k++)
    {
        cout << Rankingsarray2[k][4];
        cout << endl;
    }
    cout << endl;







    for (int qq = 0; qq < winnerslosersarrlenght; qq++)
    {
        cout << WinnersandLosersarr[qq][0];
        cout << " ";
        cout << WinnersandLosersarr[qq][1];
        cout << endl;
    }
    cout << endl;

    //Create a table with columns and rows for losers and winners to compare with the array

    int p = 0;
    int k = 0;

    for (int c = 0; c < winnerslosersarrlenght; c++)
    {
        for (int q = c + 1; q < winnerslosersarrlenght; q++)
        {
            if (WinnersandLosersarr[c][0] == WinnersandLosersarr[q][0])
            {
                WinnersandLosersarr[q][0] = "";
            }
        }
        if (WinnersandLosersarr[c][0] != "")
        {
            WinnersandLosersarr[p][4] = WinnersandLosersarr[c][0];
            p++;
        }
    }

    for (int c = 0; c < winnerslosersarrlenght; c++)
    {
        for (int q = c + 1; q < winnerslosersarrlenght; q++)
        {
            if (WinnersandLosersarr[c][1] == WinnersandLosersarr[q][1])
            {
                WinnersandLosersarr[q][1] = "";
            }
        }
        if (WinnersandLosersarr[c][1] != "")
        {
            WinnersandLosersarr[k][5] = WinnersandLosersarr[c][1];
            k++;
        }
    }


    /* for (int g = 0; g < p; g++)
     {
         cout << WinnersandLosersarr[g][4];
         cout << endl;
     }
     cout << endl;

     for (int g = 0; g < k; g++)
     {
         cout << WinnersandLosersarr[g][5];
         cout << endl;
     }
     cout << endl;
     */

     //Check for same entries---------Only for small number of voters--If yes then add names to array

    for (int i = 0; i < p; i++)
    {
        int NameFound1 = 0;
        for (int j = 0; j < k; j++)
        {
            if (WinnersandLosersarr[i][4] == WinnersandLosersarr[j][5])
            {
                NameFound1 = 1;
            }
        }
        if (NameFound1 == 0)
        {
            WinnersandLosersarr[k][5] = WinnersandLosersarr[i][4];
            k++;

        }
    }



    for (int i = 0; i < k; i++)
    {
        int NameFound2 = 0;
        for (int j = 0; j < p; j++)
        {
            if (WinnersandLosersarr[i][5] == WinnersandLosersarr[j][4])
            {
                NameFound2 = 1;
            }
        }
        if (NameFound2 == 0)
        {
            WinnersandLosersarr[p][4] = WinnersandLosersarr[i][5];
            p++;
        }
    }


    for (int g = 0; g < p; g++)
    {
        cout << WinnersandLosersarr[g][4];
        cout << endl;
    }
    cout << endl;

    for (int g = 0; g < k; g++)
    {
        cout << WinnersandLosersarr[g][5];
        cout << endl;
    }
    cout << endl;
    //---------------------------------------------------------------------------------------------------
    //Make arrays equal
    for (int t = 0; t < p; t++)
    {
        for (int m = 0; m < k; m++)
        {
            if (WinnersandLosersarr[t][4] == WinnersandLosersarr[m][5])
            {
                swap(WinnersandLosersarr[t][5], WinnersandLosersarr[m][5]);
                break;
            }
        }
    }

    for (int g = 0; g < p; g++)
    {
        cout << WinnersandLosersarr[g][4];
        cout << endl;
    }
    cout << endl;

    for (int g = 0; g < k; g++)
    {
        cout << WinnersandLosersarr[g][5];
        cout << endl;
    }

    cout << endl;


    //Filling the Rankingsmatrix with Scores 
    int c = 0;
    int d = 0;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < k; j++)
        {
            for (int z = 0; z < winnerslosersarrlenght; z++)
            {
                if (WinnersandLosersarr[z][2] == WinnersandLosersarr[j][4] && WinnersandLosersarr[z][3] == WinnersandLosersarr[i][5])
                {
                    Electionarray[j][i] = ++c;
                }
                if (WinnersandLosersarr[z][3] == WinnersandLosersarr[j][4] && WinnersandLosersarr[z][2] == WinnersandLosersarr[i][5])
                {
                    Electionarray[j][i] = --c;
                }
                else if (WinnersandLosersarr[j][4] == WinnersandLosersarr[i][5])
                {
                    c = 0;
                    Electionarray[j][i] = c;
                }
            }
            Pairstocheck[d][0].PairstoLock = WinnersandLosersarr[i][4];
            Pairstocheck[d][1].PairstoLock = WinnersandLosersarr[j][5];
            Pairstocheck[d][2].voternumber = (c) * -1;
            d++;
            c = 0;
        }
    }

    for (int j = 0; j < k; j++)
    {
        for (int i = 0; i < p; i++)
        {
            if (Electionarray[j][i] < 0)
            {
                cout << Electionarray[j][i];
                cout << " ";
            }

            if (Electionarray[j][i] >= 0)
            {
                cout << " ";
                cout << Electionarray[j][i];
                cout << " ";
            }
        }
        cout << endl;
    }
    winners = p;
    losers = k;

    for (int xx = 0; xx < d; xx++)
    {
        cout << "<";
        cout << Pairstocheck[xx][0].PairstoLock;
        cout << ",";
        cout << Pairstocheck[xx][1].PairstoLock;
        cout << ">";
        cout << " ";
    }
    cout << endl;

    for (int xx = 0; xx < d; xx++)
    {
        cout << "<";
        cout << Pairstocheck[xx][2].voternumber;
        cout << ">";
        cout << "      ";
    }
    cout << endl;
    //Sort
    for (int j = 0; j < d; j++)
    {
        for (int n = 0; n < d; n++)
        {
            if (Pairstocheck[j][2].voternumber <= Pairstocheck[j + n][2].voternumber && Pairstocheck[j][1].PairstoLock != "" && Pairstocheck[j + n][1].PairstoLock != "" && Pairstocheck[j][0].PairstoLock != "" && Pairstocheck[j + n][0].PairstoLock != "")
            {
                swap(Pairstocheck[j][2].voternumber, Pairstocheck[j + n][2].voternumber);
                swap(Pairstocheck[j][0].PairstoLock, Pairstocheck[j + n][0].PairstoLock);
                swap(Pairstocheck[j][1].PairstoLock, Pairstocheck[j + n][1].PairstoLock);
            }
        }
    }

    for (int xx = 0; xx < d; xx++)
    {
        cout << "<";
        cout << Pairstocheck[xx][0].PairstoLock;
        cout << ",";
        cout << Pairstocheck[xx][1].PairstoLock;
        cout << ">";
        cout << " ";
    }
    cout << endl;

    for (int xx = 0; xx < d; xx++)
    {
        cout << "<";
        cout << Pairstocheck[xx][2].voternumber;
        cout << ">";
        cout << "      ";
    }
    cout << endl;

    int h = 0;

    //Delete 0 and negative entries
    for (int xx = 0; xx < d; xx++)
    {
        if (Pairstocheck[xx][2].voternumber > 0)
        {
            Pairstocheck[xx][3].PairstoLock = Pairstocheck[xx][0].PairstoLock;
            Pairstocheck[xx][4].PairstoLock = Pairstocheck[xx][1].PairstoLock;
            Pairstocheck[xx][5].voternumber = Pairstocheck[xx][2].voternumber;
            h++;
        }
    }

    for (int xx = 0; xx < h; xx++)
    {
        cout << "<";
        cout << Pairstocheck[xx][3].PairstoLock;
        cout << ",";
        cout << Pairstocheck[xx][4].PairstoLock;
        cout << ">";
        cout << " ";
    }
    cout << endl;

    for (int xx = 0; xx < h; xx++)
    {
        cout << "<";
        cout << Pairstocheck[xx][5].voternumber;
        cout << ">";
        cout << "      ";
    }
    cout << endl;




}

// Print the winner of the election??
void print_winner(void)
{



    return;
}
