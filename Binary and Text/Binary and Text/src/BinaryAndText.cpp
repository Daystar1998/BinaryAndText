/******************************************************************************
	Name: binaryAndText.cpp

	Des:
		This program will read a binary file and output the data into a text
		file

	Author: Matthew Day

	Due Date: 9/8/2019
******************************************************************************/

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

/******************************************************************************
		Name: readAverageRating

		Des:
			Reads ratings from a binary file and return the average of those
			ratings

		Params:
			fin - type ifstream &, the file to be read from

		Return:
			type double, the average rating

******************************************************************************/
double readAverageRating(ifstream &fin) {

	double result = 0;

	if (fin.good()) {

		unsigned char numberOfRatings;
		unsigned char *ratings;

		// Read the number of ratings
		fin.read((char *)& numberOfRatings, sizeof numberOfRatings);

		// Check if memory was properly allocated
		try {

			ratings = new unsigned char[numberOfRatings];
		} catch (bad_alloc &e) {

			cerr << "Error: Could not allocate memory " << e.what() << endl;
			exit(EXIT_FAILURE);
		}

		// Read the ratings;
		fin.read((char *)ratings, numberOfRatings);

		for(int i = 0; i < numberOfRatings; i++){

			result += ratings[i];
		}

		result /= numberOfRatings;

		delete[] ratings;
	}

	return result;
}

/******************************************************************************
		Name: readFile

		Des:
			Reads data from a binary file

		Params:
			filename - type string &, the name of the file
			idsAndRatings - map<short, double> &, map of the ids to the
				average ratings

******************************************************************************/
void readFile(string &filename, map<short, double> &idsAndRatings) {

	unsigned char numberOfIds;
	short idNumber;
	double averageRating;

	ifstream fin(filename, ios::in | ios::binary);

	if (fin.good()) {

		// Read the number of ids
		fin.read((char *)& numberOfIds, sizeof numberOfIds);

		for (int i = 0; i < numberOfIds; i++) {

			// Read the id;
			fin.read((char *)& idNumber, sizeof idNumber);

			// Read the average of the ratings
			averageRating = readAverageRating(fin);

			// Enter the id and averageRating pair into the idsAndRatings map
			idsAndRatings[idNumber] = averageRating;
		}
	}

	fin.close();
}

int main() {

	string fileName = "ratingsFile.dat";

	map<short, double> idsAndRatings;

	readFile(fileName, idsAndRatings);

	return 0;
}