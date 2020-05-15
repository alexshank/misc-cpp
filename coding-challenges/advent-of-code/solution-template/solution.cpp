#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    // read input file
    ifstream inputFile;
    string line;
    inputFile.open("input.txt");
    if(inputFile.is_open()){
        while(getline(inputFile, line, ',')){

        }
    }
    inputFile.close();
    cout << "Final answer: " << line << endl;
}