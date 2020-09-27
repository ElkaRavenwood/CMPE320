//============================================================================
// Name        : insultgenerator_17jhcw.cpp
// Author      : Jamie Won
// Version     : 0.0
// Description : A Shakespearian Insult Generator Header File
// Date		   : October 2, 2020
//============================================================================

#pragma once // ensure this file is only declared once, regardless of how many times it's included in other files

#include <string>
#include <vector>
using namespace std;

class InsultGenerator {

	public:
		void initialize(); // reads file and splits to attributes
		string talkToMe(); // returns a single insult
		vector<string> generate(const int numInsults); // generates a specific number of insults
		void generateAndSave(const string& filename, const int num); // generates a specific number of insults and saves them

	private:
		vector<vector <string> > attributes; // stores the attributes read from InsultsSource.txt
};

class FileException {
	public:
		FileException(const string& message); // constructor takes in a message
		string& what();
	private:
		string message; // private member containing error message
};

class NumInsultsOutOfBounds {
	public:
		NumInsultsOutOfBounds(const string& message); // constructor takes in a message
		string& what();
	private:
		string message; // private member containing error message
};
