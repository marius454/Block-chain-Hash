// Hash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

int numDigits(unsigned long long number);

int main()
{

	std::string strA, strB, strC, strD;
	char check = 'y';
	while (check != 'n') {
		unsigned long long int a = 0x4F2C01A9;
		unsigned long long int b = 0x586176D4;
		unsigned long long int c = 0x9A097473;
		unsigned long long int d = 0x51B4A584;
		std::string input;
		unsigned short int menu;
		std::cout << "Choose what you wish to do" << std::endl;
		std::cout << "1)Take the input for hash from text file" << std::endl;
		std::cout << "2)Input the text you wish to hash directly" << std::endl;
		std::cin >> menu;
		if (menu == 1) {
			std::ifstream testfile("C:\\Users\\Marius\\Desktop\\5 semestro uzrasai\\Uzduotys\\Block-chain\\Hash\\Test_files\\The Name of the Wind (1).txt");
			testfile.seekg(0, std::ios::end);
			input.reserve(testfile.tellg());
			testfile.seekg(0, std::ios::beg);

			input.assign((std::istreambuf_iterator<char>(testfile)), std::istreambuf_iterator<char>());
			testfile.close();
		}
		if (menu == 2) {
			std::cout << "Type the text you wish to hash:" << std::endl;
			std::cin.ignore();
			std::getline(std::cin, input);
		}
		char *ch = new char[input.size() + 1];
		strcpy_s(ch, input.size() + 1, input.c_str());
		for (unsigned long i = 0; i <= input.size(); i++) {
			int seed = (int)ch[i];
			a = a * (int)round(pow(seed+1, 3.14159));
			b = b * (int)round(pow(seed+1, 2.71828));
			c = c * (int)round(pow(seed+1, sqrt(2)));
			d = d * (int)round(pow(seed+1, 1.61803));

			if (i == input.size()) {
				std::stringstream streamA;
				streamA << std::hex << a << std::endl;
				std::string result(streamA.str());
				strA = result.substr(0, 8);
				std::reverse(strA.begin(), strA.end());

				std::stringstream streamB;
				streamB << std::hex << b << std::endl;
				result = streamB.str();
				strB = result.substr(0, 8);
				std::reverse(strB.begin(), strB.end());

				std::stringstream streamC;
				streamC << std::hex << c << std::endl;
				result = streamC.str();
				strC = result.substr(0, 8);
				std::reverse(strC.begin(), strC.end());

				std::stringstream streamD;
				streamD << std::hex << d << std::endl;
				result = streamD.str();
				strD = result.substr(0, 8);
				std::reverse(strD.begin(), strD.end());
			}
			else {
				int rem;
				unsigned long long int reverseA = 0x0, reverseB = 0x0, reverseC = 0x0, reverseD = 0x0;
				int digA = numDigits(a), digB = numDigits(b), digC = numDigits(c), digD = numDigits(d);
				a = a / std::pow(16, digA-7);
				b = b / std::pow(16, digB-7);
				c = c / std::pow(16, digC-7);
				d = d / std::pow(16, digD-7);
				for (unsigned short int i = 0; i <= 9; i++)
				{
					rem = a % 16;
					reverseA = reverseA * 16 + rem;
					a /= 16;
					rem = b % 16;
					reverseB = reverseB * 16 + rem;
					b /= 16;
					rem = c % 16;
					reverseC = reverseC * 16 + rem;
					c /= 16;
					rem = d % 16;
					reverseD = reverseD * 16 + rem;
					d /= 16;
				}
				a = reverseA;
				b = reverseB;
				c = reverseC;
				d = reverseD;
			}
		}
		std::cout << std::hex << strA << strB << strC << strD << std::endl;

		std::cout << "Do you wish to hash another test? y/n ";
		std::cin >> check;
	}
	return 0;
}

int numDigits(unsigned long long number)
{
	int digits = 0;
	while (number > 15) {
		number /= 16;
		digits++;
	}
	return digits;
}
