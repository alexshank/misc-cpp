#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// calculate adjusted fuel requirements
int recursiveFuel(int fuelSum){
    int additionalFuel = floor(fuelSum / 3) - 2;
    if(additionalFuel < 0)
        return 0;
    else{
        return additionalFuel + recursiveFuel(additionalFuel);
    }
}

int main(){
    // read input file
    ifstream inputFile;
    string line;
    vector<int> weights;
    inputFile.open("input.txt");
    if(inputFile.is_open()){
        while(getline(inputFile, line)){
            weights.push_back(stoi(line));
        }
    }
    inputFile.close();

    // calculate fuel requirements
    int fuelSum = 0;
    int adjustedFuelSum = 0;
    vector<int>::iterator it = weights.begin();
    for(it; it != weights.end(); it++){
        fuelSum += floor(*it / 3) - 2;          // part I
        adjustedFuelSum += recursiveFuel(*it);  // part II
    }
    cout << "Fuel sum 1: " << fuelSum << endl;
    cout << "Fuel sum 2: " << adjustedFuelSum << endl;
}