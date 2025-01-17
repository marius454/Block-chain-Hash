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
#include <bitset>

std::string menu();
int numDigits(unsigned long long number);
void testPairs(int argc, char** argv);

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
			std::ifstream in(filename);
			if (!in)
			{
				std::cerr << "Cannot open the File : " << filename << std::endl;
				return false;
			}
			in.seekg(0, std::ios::end);
			input[0].reserve(in.tellg());
			in.seekg(0, std::ios::beg);

			input[0].assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
			in.close();
		}
		else if (argc == 3 && (std::string)argv[argc - 2] == "lines") {
			std::string filename = "C:\\Users\\Marius\\Desktop\\5 semestro uzrasai\\Uzduotys\\Block-chain\\Hash\\Test_files\\" + (std::string)argv[argc - 1];
			std::ifstream in(filename);
			if (!in)
			{
				std::cerr << "Cannot open the File : " << filename << std::endl;
				return false;
			}
			std::string str;
			while (std::getline(in, str))
			{
				if (str.size() > 0)
					input.push_back(str);
			}
			in.close();
		}
		else if (argc == 3 && (std::string)argv[argc - 2] == "pairs1") {
			testPairs(argc, argv);
			printf("Total time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
			return 0;
		}
		else if (argc == 3 && (std::string)argv[argc - 2] == "pairs2") {
			testPairs(argc, argv);
			printf("Total time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
			return 0;
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
			for (unsigned long i = 0; i <= input[z].size(); i++) {
				t1 = std::chrono::high_resolution_clock::now();
				int seed = (int)ch[i];
				for (unsigned short j = 0; j < n; j++) {
					hash[j] = hash[j] * (int)round(pow(seed + 1, constants[j]));
				}

				if (i == input[z].size()) {
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
			std::string resultHash;
			for (unsigned short i = 0; i < n; i++) {
				resultHash.append(strHash[i]);
			}
			if ((std::string)argv[argc - 2] != "lines") {
				std::cout << resultHash << std::endl;
			}
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
		std::ifstream testfile("C:\\Users\\Marius\\Desktop\\5 semestro uzrasai\\Uzduotys\\Block-chain\\Hash\\Test_files\\empty.txt");
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



void testPairs(int argc, char** argv)
{
	long total = 0;
	unsigned short max = 0, min = 129;
	unsigned int collisions = 0;
	short n = 4;
	long long duration = 0;
	auto t1 = std::chrono::high_resolution_clock::now();
	auto t2 = std::chrono::high_resolution_clock::now();
	double constants[4]{ 3.14159, 2.71828, sqrt(2), 1.61803 };
	std::string pair, pair1, pair2;
	std::vector<std::string> input;
	std::string filename = "C:\\Users\\Marius\\Desktop\\5 semestro uzrasai\\Uzduotys\\Block-chain\\Hash\\Test_files\\" + (std::string)argv[argc - 1];
	std::ifstream in(filename);
	unsigned int i = 0;
	while (std::getline(in, pair)) {
		if (pair.size() > 0) {
			input.push_back(pair);
		}
	}

	for (unsigned int z = 0; z < input.size(); z++) {
		pair1 = input[z].substr(0, 5);
		pair2 = input[z].substr(6, 11);
		std::string strHash[4];
		unsigned long long hash1[4]{ 0x4F2C01A9, 0x586176D4, 0x9A097473, 0x51B4A584 };
		char *ch = new char[pair1.size() + 1];
		strcpy_s(ch, pair1.size() + 1, pair1.c_str());
		for (unsigned long i = 0; i <= pair1.size(); i++) {
			int seed = (int)ch[i];
			t1 = std::chrono::high_resolution_clock::now();
			for (unsigned short j = 0; j < n; j++) {
				hash1[j] = hash1[j] * (int)round(pow(seed + 1, constants[j]));
			}

			if (i == pair1.size()) {
				for (unsigned short j = 0; j < n; j++) {
					std::stringstream stream;
					stream << std::hex << hash1[j];
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
					hash1[j] = hash1[j] / std::pow(16, numDigits(hash1[j]) - 8);
				}
				for (unsigned short j = 0; j <= 9; j++)
				{
					for (unsigned short k = 0; k < n; k++) {
						rem = hash1[k] % 16;
						reverse[k] = reverse[k] * 16 + rem;
						hash1[k] /= 16;
					}
				}
				for (unsigned short j = 0; j < n; j++) {
					hash1[j] = reverse[j];
				}
			}
			t2 = std::chrono::high_resolution_clock::now();
			duration = duration + std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		}
		std::string resultHash1;
		for (unsigned short i = 0; i < n; i++) {
			resultHash1.append(strHash[i]);
		}


		unsigned long long hash2[4]{ 0x4F2C01A9, 0x586176D4, 0x9A097473, 0x51B4A584 };
		char *ch2 = new char[pair2.size() + 1];
		strcpy_s(ch2, pair2.size() + 1, pair2.c_str());
		for (unsigned long i = 0; i <= pair2.size(); i++) {
			int seed = (int)ch2[i];
			t1 = std::chrono::high_resolution_clock::now();
			for (unsigned short j = 0; j < n; j++) {
				hash2[j] = hash2[j] * (int)round(pow(seed + 1, constants[j]));
			}

			if (i == pair2.size()) {
				for (unsigned short j = 0; j < n; j++) {
					std::stringstream stream;
					stream << std::hex << hash2[j];
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
					hash2[j] = hash2[j] / std::pow(16, numDigits(hash2[j]) - 8);
				}
				for (unsigned short j = 0; j <= 9; j++)
				{
					for (unsigned short k = 0; k < n; k++) {
						rem = hash2[k] % 16;
						reverse[k] = reverse[k] * 16 + rem;
						hash2[k] /= 16;
					}
				}
				for (unsigned short j = 0; j < n; j++) {
					hash2[j] = reverse[j];
				}
			}
			t2 = std::chrono::high_resolution_clock::now();
			duration = duration + std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		}
		std::string resultHash2;
		for (unsigned short i = 0; i < n; i++) {
			resultHash2.append(strHash[i]);
		}
		if (resultHash1 == resultHash2) {
			std::cout << resultHash1 << std::endl << resultHash2 << std::endl;
			std::cout << pair1 << std::endl << pair2 << std::endl << std::endl;
			collisions++;
		}
		int i = 0, count = 0;
		std::string str1, str2;
		if ((std::string)argv[argc - 2] == "pairs2") {
			std::stringstream stream1;
			std::stringstream stream2;
			str1 = ""; str2 = "";
			for (std::size_t i = 0; i < resultHash1.size(); ++i)
			{
				str1 += std::bitset<4>(resultHash1.c_str()[i]).to_string();
				str2 += std::bitset<4>(resultHash2.c_str()[i]).to_string();
			}
			while (str1[i] != '\0')
			{
				if (str1[i] != str2[i])
					count++;
				i++;
			}
			total = total + count;
			if (count > max) max = count;
			if (count < min) min = count;
		}
		//std::cout << resultHash1 << std::endl << resultHash2 << std::endl << std::endl;
	}
	if ((std::string)argv[argc - 2] == "pairs2") {
		std::cout << "vidutiniskai skiriasi " << (double)total / (double)input.size() / 1.28 << "% bitu" << std::endl;
		std::cout << "maziausias skirtumas" << (double)min / 1.28 << "% bitu" << std::endl;
		std::cout << "didziausias skirtumas" << (double)max / 1.28 << "% bitu" << std::endl;
	}
	std::cout << collisions << std::endl;
	double dur = (double)duration * 0.000001;
	std::cout << "Time taken by hashing: " << std::dec << dur << "s" << std::endl;
}
