//A programm to build pyramdies consisting of #

#include <iostream>
using namespace std;

int main()
{
    int a, b, c, d, e, f, g, h, i;

    std::cout << "Please enter a number from 1 to 8: ";
    std::cin >> i;
    std::cout << "The value you entered is " << i;
    std::cout << "\n";

    if (0 <= i && i <= 8)
    {
        for (a = 9 - i; a <= 8; a++)
        {
            std::cout << "\n";

            for (c = 7; c >= a; c--)
            {
                std::cout << " ";
            }

            for (b = 1; b <= a; b++)
            {
                std::cout << "#";
            }
        }
        return 0;
    }

