//============================================================================
// Name        : insultgenerator_17jhcw.cpp
// Author      : Jamie Won
// Version     : 0.0
// Description : A Shakespearian Insult Generator
// Date		   : October 2, 2020
//============================================================================

#include <iostream>
#include <fstream>
#include <algorithm>    // std::find
#include <string>
#include <vector>

#include "insultgenerator_17jhcw.h"

#define FILEIN "InsultsSource.txt"
#define COLUMNS 3

using namespace std;

FileException::FileException(const string& message) : message(message) {}
string& FileException::what() { return message;}


NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& message) : message(message) {}
string& NumInsultsOutOfBounds::what() { return message;}

/**
 * Reads and splits file into three rows. The file is read word by word, and the words are then put into the corresponding column in the class vector attributes.
 */
void InsultGenerator::initialize() {

	string line, word;
	int count(0);

	// tries to open file
	ifstream fileIn(FILEIN);

	// makes a 2D vector, w/ 3 rows of words
	vector<vector<string> > parsed(COLUMNS);

	if (fileIn.fail()) throw FileException("Unable to read file.");

	// Demonstrating another way to read the file.
	while (fileIn >> word) {
		parsed[count%COLUMNS].push_back(word);
		count ++;
	}

	// closes file
	fileIn.close();

	// Sets the parsed array into the private attributes member
	InsultGenerator::attributes = parsed;

} // end initialize

/**
 * Generates a single Shakespearian insult using the values in the attributes member of the class
 * @return The insult generated
 */
string InsultGenerator::talkToMe() {
	int length(InsultGenerator::attributes[0].size());
	string insult("Thou");
	for (int i = 0; i < COLUMNS; i ++) {
		insult += " " + InsultGenerator::attributes[i][rand() % length];
	}
	insult += "!"; // add an exclamation mark
	return insult;
} // end talkToMe

/**
 * Using InsultGenerator::talkToMe, generates a number of unique insults
 * @param numInsults the number of insults to generate
 * @return the vector of length numInsults of insults generated
 */
vector<string> InsultGenerator::generate(const int numInsults) {

	vector <string> insults(0);

	// if out of bounds
	if (numInsults < 1 || numInsults > 10000) {
		throw NumInsultsOutOfBounds("Insult number is out of bounds.");
		return insults;
	}
	// if an unique insult, saves it to the insults array
	for (int i = 0; i < numInsults; i ++) {
		string anInsult(InsultGenerator::talkToMe());
		// Checks to ensure it is an unique insult. Without this, the function is a lot faster.
		while(find(insults.begin(), insults.end(), anInsult) != insults.end()) anInsult = InsultGenerator::talkToMe();
		insults.push_back(anInsult);
	}
	return insults;
} // end generate

/**
 * Using InsultGenerator::generate, generates a number of unique insults and saves them to a file
 * @param filename the name of the file to write
 * @param numInsults the number of insults to generate
 */
void InsultGenerator::generateAndSave(const string& filename, const int numInsults) {
	ofstream fileOut(filename);

	if (fileOut.fail()) throw FileException("Unable to write to file");

	vector<string> results(InsultGenerator::generate(numInsults));
	for (int i = 0; i < results.size(); i ++) {
		fileOut << results[i] << endl;
	}

	fileOut.close();
} // end generateAndSave

