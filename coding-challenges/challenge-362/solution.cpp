/*
 * Alex Shank
 * June 2016
 * r/DailyProgrammer Challenge 362
 */
#include <iostream>
#include <string>
#include <vector>
#include <utility>	// for std::pair and std::make_pair
using namespace std;

// global variables
string message;
int columns;
int rows;
string direction;
string encryption = "";

/*
 * get the user's input string and extract the
 * needed parameters from it.
 *
 * NOTE: user's input string should be 
 * 	 "string" (columns, rows) <clockwise/counter-clockwise>
 * NOTE: substr in C++ and Java work differently
 */
void getParameters(){
	// get user's input string
	cout << endl << "Enter \"string\" (c, r) <clockwise/counter-clockwise>" << endl;
	string in;
	getline(cin, in);
	cout << endl;
	
	// get message 
	int secondQuotationIndex = in.find('"', 1);
	message = in.substr(1, secondQuotationIndex - 1);
	in = in.substr(secondQuotationIndex + 2);

	// get rid of whitespace and punctuation in message
	string temp = "";
	for(int i = 0; i < message.length(); i++){
		if(!isspace(message.at(i)) && !ispunct(message.at(i))){
			temp += message.at(i);
		}
	}
	message = temp;

	// get columns 
	int commaIndex = in.find(',');
	columns = stoi(in.substr(1, commaIndex - 1));
	in = in.substr(commaIndex + 1);

	// get rows
	rows = stoi(in.substr(0, in.find(')')));

	// get direction
	direction = in.substr(in.find(')') + 2);
}	


/*
 * return input message in all caps with no whitespace 
 */
void standardizeMessage(){
	// get all caps version of messge
	string temp = "";
	for(int i = 0; i < message.length(); i++){
		temp += toupper(message.at(i));
	}	

	// add needed X's to end of string
	int neededLength = rows * columns - message.length();
	for(int i = 0; i < neededLength; i++){
		temp += "X";
	}
	message = temp;
}


/*
 * add chars to global encryption string based on
 * movement across rows or up and down 
 * columns
 */
void addCharsByMovement(int startC, int startR, int endC, int endR){
	// moving in row
	if(startC != endC){
		// moving right
		if(startC < endC){
			startC++;
			while(startC <= endC){
				encryption += message.at(startC + startR * columns);
				startC++;
			}			
		}
		// moving left
		else{
			startC--;
			while(startC >= endC){
				encryption += message.at(startC + startR * columns);
				startC--;
			}	
		}
	}
	// moving in column 
	else if(startR != endR){
		// moving down 
		if(startR < endR){
			startR++;
			while(startR <= endR){
				encryption += message.at(startC + startR * columns);
				startR++;
			}
		}
		// moving up 
		else{
			startR--;
			while(startR >= endR){
				encryption += message.at(startC + startR * columns);
				startR--;
			}
		}

	}
}


/*
 * This function sets start and end coordinates
 * for traversing the initial message grid based
 * on clockwise spiral. The character at each
 * coordinate is then added to the encrypted message.
 */
void createClockwiseEncryption(){
	// variables for start and end coordinates
	int changeR = rows - 1;
	int changeC = (columns - 1) * -1;
	int startC = columns - 1, startR = 0, endC = startC, endR = startR;

	// add starting coordinate always
	encryption += message.at(startC + startR * columns);
	
	// keep changing start and end coordinates until vector is correct size
	while(encryption.length() < rows * columns){
		// move up/down row 
		startC = endC;
		startR = endR;
		endR = endR + changeR;
		/* 
		 * the first and last columns get
		 * completely traversed, so the
		 * added condition is needed at the start
		 */
		if(changeR > 0 && encryption.length() > 1){
			changeR--;
		}else if(changeR < 0){
			changeR++;
		}
		changeR = changeR * -1;
		addCharsByMovement(startC, startR, endC, endR);

		// move across column
		startC = endC;
		startR = endR;
		endC = endC + changeC;
		if(changeC > 0){
			changeC--;
		}else{
			changeC++;
		}
		changeC = changeC * -1;
		addCharsByMovement(startC, startR, endC, endR);
	}
}


/*
 * This function sets start and end coordinates
 * for traversing the initial message grid based
 * on counter-clockwise spiral. The character at each
 * coordinate is then added to the encrypted message.
 */
void createCounterClockwiseEncryption(){
	// variables for start and end coordinates
	int changeR = rows - 1;
	int changeC = (columns - 1) * -1;
	int startC = columns - 1, startR = 0, endC = startC, endR = startR;

	// add starting coordinate always
	encryption += message.at(startC + startR * columns);
	
	// keep changing start and end coordinates until vector is correct size
	while(encryption.length() < rows * columns){
		// move across column
		startC = endC;
		startR = endR;
		endC = endC + changeC;
		/* 
		 * the first and last rows get
		 * completely traversed, so the
		 * added condition is needed at the start
		 */
		if(changeC > 0 && encryption.length() > 1){
			changeC--;
		}else if(changeR < 0){
			changeC++;
		}
		changeC = changeC * -1;
		addCharsByMovement(startC, startR, endC, endR);
		
		// move up/down row 
		startC = endC;
		startR = endR;
		endR = endR + changeR;
		/* 
		 * the first and last columns get
		 * completely traversed, so the
		 * added condition is needed at the start
		 */
		if(changeR > 0){
			changeR--;
		}else{ 
			changeR++;
		}
		changeR = changeR * -1;
		addCharsByMovement(startC, startR, endC, endR);
	}
}


/*
 * print the message grid to the console
 */
void printGrid(){
	cout << "----------Grid----------";	
	for(int i = 0; i < message.length(); i++){
		if(i % columns == 0){
			cout << endl;
		}
		cout << message.at(i) << " ";
	}
	cout << endl << "------------------------" << endl << endl;
}


/*
 * main program functionality
 */
int main(){
	// get program parameters
	getParameters();

	// make message all caps and correct length 
	standardizeMessage();

	// print the message grid
	printGrid();

	// create clockwise vector
	if(direction.compare("clockwise") == 0){
		createClockwiseEncryption();	
	}else if(direction.compare("counter-clockwise") == 0){
		createCounterClockwiseEncryption();
	}else{
		cout << "Error: You must specify \"clockwise\" or \"counter-clockwise\"" << endl;
	}

	// print encrypted message
	cout << "Encryption: " << encryption << endl << endl;	
	return 0;
}
