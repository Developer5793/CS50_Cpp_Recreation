// CreditCardNumbers.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.


//A proghgramm to check if Credit Card numbers are valid//



#include <cmath>
#include <iostream>
using namespace std;

int main()
{
	while (true) {
		long long int result, sum = 0;
		long long int i, k, z, f, d, g, checkfraud;

		std::cout << "Please enter your Credit Card Number \n";
		std::cin >> i; "\n";
		std::cout << "The number is: ";
		std::cout << i << endl;
		
			z = i;
			k = 0;
			//Algorithm to count the lenght of an integer
			long long int CountInt = z;
			long long int len = 1;
			if (CountInt > 0) {
				for (len = 0; CountInt > 0; len++) {
					CountInt = CountInt / 10;
				}
			}
		if (len == 13 || len == 15 || len == 17) {
			//Backtesting how to get the values
			//result = z % k;
			//std::cout << result << endl;

			//result = z / k%k;
			//std::cout << result << endl;

			//result = z /(k*k)%k;
			//std::cout << result << endl;

			//result = z / (k*k*k) % k;
			//std::cout << result << endl;

			k = len;
			for (f = 1; f <= len; f++) {
				k = k - 1;
				d = pow(10, k);

				if (k % 2 == 0) {
					result = z / (d) % 10;
					std::cout << result << endl;

				}
				else if (k % 2 == 1) {
					result = (z / (d) % 10) * 2;
					std::cout << result << endl;
				}
				sum += result;
			}
			checkfraud = sum % 10;
			std::cout << "Sum: ";
			std::cout << sum << endl;
			std::cout << checkfraud << endl;

			if (checkfraud != 0) {
				std::cout << "The Card is fraudulent" << endl;
			}
			else if (checkfraud == 0) {
				std::cout << "The number is valid" << endl;
			}
		}
		else if(len != 13 && len != 15 && len != 17) {
			std::cout << "Incorrect Number of Digits" << endl;
		}
	}
}



	




