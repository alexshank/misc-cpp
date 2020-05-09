#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

const int ADD_CODE = 1;
const int MULT_CODE = 2;
const int HALT_CODE = 99;
const int SOLUTION_VAL = 19690720;

int executeProgram(vector<int> program, int noun, int verb){
    // try different noun/verb initial conditions
    program[1] = noun;
    program[2] = verb;

    // execute program
    for(int i = 0; i < program.size(); i += 4){
        if(program[i] == ADD_CODE){
            program[program[i+3]] = program[program[i+1]] + program[program[i+2]];
        }else if(program[i] == MULT_CODE){
            program[program[i+3]] = program[program[i+1]] * program[program[i+2]];
        }else if(program[i] == HALT_CODE){
            break;
        }else{
            return 1;
        }
    }
    return program[0];
}

int main(){
    // read input file
    ifstream inputFile;
    string line;
    vector<int> codes;
    inputFile.open("input.txt");
    if(inputFile.is_open()){
        while(getline(inputFile, line, ',')){
            codes.push_back(stoi(line));
        }
    }
    inputFile.close();

    // try different noun/verb combos
    for(int i = 0; i < 100; i++){
        for(int k = 0; k < 100; k++){
            vector<int> program = vector<int>(codes);
            if(executeProgram(program, i, k) == SOLUTION_VAL) {
                cout << "Final answer: " << (100 * i + k) << endl;
           }
        }
    }
}