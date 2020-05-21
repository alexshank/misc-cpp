#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

const int ADD_CMD = 1;              // computer system's commands 
const int MULT_CMD = 2;
const int SAVE_CMD = 3;
const int OUTPUT_CMD = 4;
const int JMP_IF_TRUE_CMD = 5;
const int JMP_IF_FALSE_CMD = 6;
const int LESS_THAN_CMD = 7;
const int EQUAL_CMD = 8;
const int HALT_CMD = 99;
const int POSITION_MODE = 0;        // parameter modes
const int IMMEDIATE_MODE = 1;
const int INPUT = 5;                // diagonstic input to program
const int ASCII_OFFSET = 48;        // convert '0' to int

/*
 * contains instruction command and parameter modes
 */
struct Instruction {
    int command;
    int mode1, mode2;   // mode 3 always position

    // parse opcode into valid instruction 
    Instruction(const int &opcode){
        string s = to_string(opcode);
        int appendCount = 5 - s.length();
        for(int i = 0; i < appendCount; i++){
            s.insert(0, "0");
        }
        command = stoi(s.substr(3,5));
        mode1 = s[2] - ASCII_OFFSET;
        mode2 = s[1] - ASCII_OFFSET;    // mode3 always position
    }
};

// get operand based on position or immediate mode
int getOperand(const vector<int> &program, const int &mode, const int &operandAddress){
    int effectiveAddress = (mode == POSITION_MODE) ? program[operandAddress] : operandAddress;
    if(effectiveAddress < program.size() && effectiveAddress >= 0){
        return program[effectiveAddress];
    }else{
        return -1;  // operand should not be needed for current instruction
    }
}

// execute instruction at given program counter, then return new program counter
int executeInstruction(vector<int> &program, const int &pc, const Instruction &instr){
    int operand1 = getOperand(program, instr.mode1, pc+1);
    int operand2 = getOperand(program, instr.mode2, pc+2);
    int newPC = 0;
    if(instr.command == ADD_CMD){
        program[program[pc+3]] = operand1 + operand2;
        newPC = pc + 4;
    }
    else if(instr.command == MULT_CMD){
        program[program[pc+3]] = operand1 * operand2;
        newPC = pc + 4;
    }
    else if(instr.command == SAVE_CMD){
        program[program[pc+1]] = INPUT;
        newPC = pc + 2;
    }
    else if(instr.command == OUTPUT_CMD){
        cout << "Output: " << operand1 << endl;
        newPC = pc + 2;
    }
    else if(instr.command == JMP_IF_TRUE_CMD){
        newPC = (operand1 != 0) ? operand2 : pc+3;
    }
    else if(instr.command == JMP_IF_FALSE_CMD){
        newPC = (operand1 == 0) ? operand2 : pc+3;
    }
    else if(instr.command == LESS_THAN_CMD){
        program[program[pc+3]] = operand1 < operand2;
        newPC = pc + 4;
    }
    else if(instr.command == EQUAL_CMD){
        program[program[pc+3]] = operand1 == operand2;
        newPC = pc + 4;
    }
    else if(instr.command == HALT_CMD){
        newPC = program.size(); // break from loop 
    }
    else{
        cout << "Invalid instruction!" << endl;
    }
    return newPC;
}

// continue until program counter invalid (HALT)
void executeProgram(vector<int> &program){
    int programCounter = 0; 
    while(programCounter < program.size()){
        Instruction instr(program[programCounter]);
        programCounter = executeInstruction(program, programCounter, instr);
    }
}

int main(){
    // read input file
    ifstream inputFile;
    string line;
    vector<int> program;
    inputFile.open("input.txt");
    while(getline(inputFile, line, ',')){
        program.push_back(stoi(line));
    }
    inputFile.close();

    executeProgram(program);
}