//A programm to build an endless pyramde consisting of Hashtags

#include <iostream>
using namespace std;

int main()
{
    int a, b, c, d, f, g, h, height, i;
    c = 1;
    std::cout << "Please enter a positive number: ";
    std::cin >> height;
    std::cout << "The value you entered is " << height;
    std::cout << "\n";

    //So 1. enter the loop which does every line one by one
    //2. Print the height of the pyramides -1 Spaces in the first line
    //3. Print the hight of the pyramide -Number of spaces = Hashtags in the first line 
    //4. Print Space and increase the decrementer c
    //5.Do Step 3 again without empty spaces and go to next line

    for (int q = 0; q < height; q++)
    {
        for (a = 0; a < height - c; a++)
        {
            cout << ' ';
        }

        for (g = 0; g < height - a; g++)

        {
            cout << '#';
        }
        c++;
        cout << " ";

        for (d = 0; d < height - a; d++)
        {
            cout << '#';
        }
        cout << endl;
    }
}
