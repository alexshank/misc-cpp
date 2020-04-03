/* Alex Shank
 * May 2018
 *
 * This program takes a list of items organized
 * as index<>name<>notes<>true/false in a text file.
 * It then builds structs out of each line and puts
 * them in a vector. The list is also reprinted to
 * an output file to confirm the structs were made.
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// item struct
struct item {
	int number;
	string name;
	string notes;
	bool wasSeen;
};

// global variabels
vector<item> list;
int START_INDEX = 0;

/*
 * get the next string contained between "<>" delimeter
 */
void getNextComponent(string &line, string &component){
	// cout << line << ", " << component << endl;
	int endIndex = line.find("<>");
	component = line.substr(START_INDEX, endIndex);
	line = line.substr(endIndex + 2);
}

/*
 * print out data contained in the struct
 */
void printItem(ofstream &out, item wip){
	if(out.is_open()){
		out << "***********************" << endl;
		out << wip.number << endl;
		out << wip.name << endl;
		out << wip.notes << endl;
		out << wip.wasSeen << endl;
	}
}

/*
 * main
 */
int main()
{
	// vars for parsing file
	string line;
	string fileName;
	ifstream textFile;

	
	ofstream out("output.txt");

	// get input file name
	cout << "Enter name of list file to parse:" << endl;
	cin >> fileName;
	textFile.open(fileName);

	// if file opens, make struct and add to vector
	while(getline(textFile, line)){

		// create vars for struct fields
		string number;
		string name;
		string notes;
		string wasSeen;

		// get item number
		getNextComponent(line, number);	
		getNextComponent(line, name);
		getNextComponent(line, notes);
		getNextComponent(line, wasSeen);

		// build item and add to list
		int iNumber = stoi(number);
		bool bWasSeen = wasSeen.compare("true") == 0;
		item wip = {iNumber, name, notes, bWasSeen};
		printItem(out, wip);
		list.push_back(wip);
		
	}
	
	// close files and end program
	textFile.close();

	out.close();
	return 0;
}
