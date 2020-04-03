/*
 * Alex Shank
 * May 2018
 *
 * Program that parses bank data into CSV format for an Excel spreadsheet.
 * This data is just selected and copied off of a PNC webpage with account
 * activity. The user must mark transactions as deductions or income.
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>	// for replacing commas in balance
using namespace std;


/*
 * variables for print formatting
 */
const int indexMaxLength = 2;
const int dateMaxLength = 11;
int descriptionMaxLength = 0;
int costMaxLength = 0;
int categoryMaxLength = 0;
int balanceMaxLength = 0;


/*
 * stuct for transactions
 */ 
struct transaction {
	int index;
	string date;
	string description;
	string cost;
	string category;
	string balance;
};


/*
 * remove spaces and tabs at beginning and end of input string
 */
string removeWhitespace(string sInput){
	// check beginning for non-whitespace (excluding $ signs)
	int startIndex = 0;
	int endIndex = sInput.length();
	for(int i = 0; i < sInput.length(); i++){
		if(isspace(sInput.at(i)) == 0 && sInput.at(i) != '$'){
			startIndex = i;
			break;
		}
	}

	// remove ending whitespace
	for(int i = sInput.length() - 1; i >= 0; i--){
		if(isspace(sInput.at(i)) == 0){
			endIndex = i + 1;
			break;
		}
	}

	// return the remaining string
	return sInput.substr(startIndex, endIndex - startIndex);
}


/*
 * remove white space from lines and mark transactions
 * as withdrawals if neccessary
 */
void cleanData(vector<string>& lines){
	for(vector<string>::iterator i = lines.begin(); i != lines.end(); ++i){
		*i = removeWhitespace(*i);
	}
}


/*
 * remove blank lines from input file
 * and split lines with double info
 */
void loadData(vector<string>& lines){
	// open read and write files
	ifstream textFile;
	textFile.open("data.txt");

	// go through entire file
	string tempStr;
	while(!textFile.eof()){
		getline(textFile, tempStr);
		if(tempStr.compare("") != 0){		// blank line being added at end for some reason?
			lines.push_back(tempStr);	
		}
	}

	// close files
	textFile.close();
}


/*
 * create objects from vector of strings
 */
void createTransactionObjects(vector<transaction>& trans, vector<string>& lines){
	// get year for creating dates
	cout << endl << "What year is this data from?" << endl;
	string year;
	getline(cin, year);
	cout << endl;
        
	// get object fields from each vector entry 
	transaction t;
	int counter = 0;
	for(int i = 0; i < lines.size(); i = i+5){
		t.index = counter++;
		t.date = lines[i] + " " + year;
		t.description = lines[i + 1];
		t.cost = "-" + lines[i + 2];	// add negative bc most transactions are deductions
		t.category = lines[i + 3];
		t.balance = lines[i + 4];

		trans.push_back(t);
	}
}


/*
 * print a given transaction field with proper formatting spaces
 */
void printWithSpaces(ostream& out, string transField, int maxLength, bool isEnd){
	int difference = maxLength - transField.length();
	for(int i = 0; i < difference; i++){
		out << " ";
	}
	cout << transField;
	if(isEnd){
		out << endl;
	}else{
		out << ", ";
	}
}


/*
 * print out the fields of a transaction in CSV format
 */
void printTransactions(ostream& out, vector<transaction>& trans, bool indexes){
	out << endl;
	for(int i = 0; i < trans.size(); i++){
		transaction t = trans.at(i);
		
		// print indexes based on parameter
		if(indexes){
			// keep consistent spacing (until 100)
			if(t.index < 10){
				out << " " << t.index << ":\t";
			}else{
				out << t.index << ":\t";
			}
		}
		printWithSpaces(out, t.date, dateMaxLength, 0);
		printWithSpaces(out, t.description, descriptionMaxLength, 0);
		printWithSpaces(out, t.cost, costMaxLength, 0);
		printWithSpaces(out, t.category, categoryMaxLength, 0);

		// need to remove comma from balance for CSV format
		t.balance.erase(remove(t.balance.begin(), t.balance.end(), ','), t.balance.end());
		printWithSpaces(out, t.balance, balanceMaxLength, 1);
	}
	out << endl;
}


/*
 * get max string lengths for each field
 */
void setTransactionMaxLengths(vector<transaction>& trans){
	for(int i = 0; i < trans.size(); i++){
		transaction t = trans.at(i);
		if(t.description.length() > descriptionMaxLength)
		{
			descriptionMaxLength = t.description.length();	
		}
		if(t.cost.length() > costMaxLength)
		{
			costMaxLength = t.cost.length();	
		}
		if(t.category.length() > categoryMaxLength)
		{
			categoryMaxLength = t.category.length();	
		}
		if(t.balance.length() > balanceMaxLength)
		{
			balanceMaxLength = t.balance.length();	
		}

	}
}


/*
 * start 
 */
int main(){
	// vector for lines
	vector<string> lines;

	// load data into vector
	loadData(lines);
	cleanData(lines);

	// create transaction objects
	vector<transaction> trans;
	createTransactionObjects(trans, lines);

	// get field max lengths for print formatting
	setTransactionMaxLengths(trans);

	// write objects out in CVS format
	printTransactions(cout, trans, 1);

	// ask which transactions are income
	cout << "Do you want to mark a transaction as income? (y/n)" << endl;
	string response;
	cin >> response;
	while(response.compare("y") == 0){
		printTransactions(cout, trans, 1);
		cout << "Enter the index of a positive transaction:" << endl;
		int x;
		cin >> x;
		trans.at(x).cost = trans.at(x).cost.substr(1, string::npos);
		cout << "Do you want to mark a transaction as income? (y/n)" << endl;
		cin >> response;
	}

	// reprint transactions
	printTransactions(cout, trans, 0);
	
	// confirm transactions and write to output file
	cout << "Are these transactions correct? (y/n)" << endl;
	cin >> response;
	cout << endl;
	if(response.compare("y") == 0){
		ofstream output("output.txt");
		printTransactions(output, trans, 0);
		output.close();
		cout << "The transactions were printed to output.txt!" << endl;
	}else{
		cout << "The transactions were not printed to output.txt." << endl;
	}
	cout << endl;

	return 0;
}
