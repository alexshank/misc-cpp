#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int RANGE_START = 272091;
const int RANGE_END = 815432;

bool valid(const int &num){
    string s = to_string(num);
    bool repeated = false;
    int repeatCount = 0;
    for(int k = 0; k < 5; k++){
        if(s[k] > s[k+1]) return false;
        if(s[k] == s[k+1]){
            if(k == 4 && repeatCount == 0){
                repeated = true;
            }
            repeatCount++;
        }else{
            if(repeatCount == 1){
                repeated = true;
            }
            repeatCount = 0;
        }
    }
    return repeated;
}

int main(){
    int count = 0;
    for(int i = RANGE_START; i <= RANGE_END; i++){
        if(valid(i)) count++;
    }
    cout << "Final answer: " << count << endl;
}