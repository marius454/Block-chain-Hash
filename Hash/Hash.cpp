// Hash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <math.h>
#include <vector>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <chrono>

std::string menu();
int numDigits(unsigned long long number);

int main(int argc, char** argv)
{
	long long duration = 0;
	clock_t tStart = clock();
	short n = 4;
	std::string strHash[4];
	char check = 'y';
	while (check != 'n') {
		
		std::vector<std::string> input;
		input.resize(1);
		std::cout << argv[argc-1] << std::endl;
		if (argc == 1) {
			input[0] = menu();
		}
		else if (argc == 2) {
			input[0] = argv[argc - 1];
		}
		else if (argc == 3 && (std::string)argv[argc - 2] == "file") {
			std::string filename = "C:\\Users\\Marius\\Desktop\\5 semestro uzrasai\\Uzduotys\\Block-chain\\Hash\\Test_files\\" + (std::string)argv[argc - 1];
			std::ifstream testfile(filename);
			testfile.seekg(0, std::ios::end);
			input[0].reserve(testfile.tellg());
			testfile.seekg(0, std::ios::beg);

			input[0].assign((std::istreambuf_iterator<char>(testfile)), std::istreambuf_iterator<char>());
			testfile.close();
		}
		else if (argc == 3 && (std::string)argv[argc - 2] == "lines") {
			// Open the File
			std::string filename = "C:\\Users\\Marius\\Desktop\\5 semestro uzrasai\\Uzduotys\\Block-chain\\Hash\\Test_files\\" + (std::string)argv[argc - 1];
			std::ifstream in(filename);
			// Check if object is valid
			if (!in)
			{
				std::cerr << "Cannot open the File : " << filename << std::endl;
				return false;
			}
			std::string str;
			// Read the next line from File untill it reaches the end.
			while (std::getline(in, str))
			{
				// Line contains string of length > 0 then save it in vector
				if (str.size() > 0)
					input.push_back(str);
			}
			in.close();
		}
		else {
			std::cout << "Error";
			return 0;
		}

		auto t1 = std::chrono::high_resolution_clock::now();
		auto t2 = std::chrono::high_resolution_clock::now();
		double constants[4]{ 3.14159, 2.71828, sqrt(2), 1.61803 };

		for (unsigned int z = 0; z < input.size(); z++) {
			unsigned long long hash[4]{ 0x4F2C01A9, 0x586176D4, 0x9A097473, 0x51B4A584 };
			char *ch = new char[input[z].size() + 1];
			strcpy_s(ch, input[z].size() + 1, input[z].c_str());
			for (unsigned long i = 0; i < input[z].size(); i++) {
				t1 = std::chrono::high_resolution_clock::now();
				int seed = (int)ch[i];
				for (unsigned short j = 0; j < n; j++) {
					hash[j] = hash[j] * (int)round(pow(seed + 1, constants[j]));
				}

				if (i == input[z].size() - 1) {
					for (unsigned short j = 0; j < n; j++) {
						std::stringstream stream;
						stream << std::hex << hash[j];
						std::string result(stream.str());
						strHash[j] = result.substr(0, 8);
						strHash[j].resize(8, '0');
						std::reverse(strHash[j].begin(), strHash[j].end());
					}
				}
				else {
					int rem;
					unsigned long long reverse[4]{ 0x0, 0x0, 0x0, 0x0 };
					for (unsigned short j = 0; j < n; j++) {
						hash[j] = hash[j] / std::pow(16, numDigits(hash[j]) - 8);
					}
					for (unsigned short j = 0; j <= 9; j++)
					{
						for (unsigned short k = 0; k < n; k++) {
							rem = hash[k] % 16;
							reverse[k] = reverse[k] * 16 + rem;
							hash[k] /= 16;
						}
					}
					for (unsigned short j = 0; j < n; j++) {
						hash[j] = reverse[j];
					}
				}
				t2 = std::chrono::high_resolution_clock::now();
				duration = duration + std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			}

			for (unsigned short i = 0; i < n; i++) {
				std::cout << std::hex << strHash[i];
			}
			std::cout << std::endl;
		}
		if (argc == 1) {
			std::cout << "Do you wish to hash another test? y/n ";
			std::cin >> check;
		}
		else {
			check = 'n';
		}
	}
	double dur = (double)duration * 0.000001;
	std::cout << "Time taken by hashing: " << std::dec << dur << "s" << std::endl;
	printf("Total time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	return 0;
}

std::string menu() {
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
	return input;
}





int numDigits(unsigned long long number)
{
	int digits = 0;
	while (number > 0) {
		number /= 16;
		digits++;
	}
	return digits;
}
