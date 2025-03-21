#include <vector>
#include <limits>
#include <iostream>
#include <string>

using namespace std;
/**************************************/
int getSmallestNumber(vector<int> v, int k){
    int smallestNumber = std::numeric_limits<int>::max();
    for (int i = 0; i < v.size()-1; ++i){
        string num;
        num.append(to_string(v[i]));
        for (int j = i+1; j-i <= k  && v.size()-1 - j >= k; ++j){
            num.append(to_string(v[j]));
        }
        if(stoi(num) < smallestNumber)
            smallestNumber = stoi(num);   
    }

    return smallestNumber;
}
/*************************************/
int main(){

    vector<int> v = {8,1,4,2,5,2};

    int SmallestNumber = getSmallestNumber(v,4);
    

    cout << SmallestNumber;

    return 0;
}