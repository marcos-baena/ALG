#include <vector>

using namespace std;
/**************************************/
int getSmallestNumber(vector<int> v, int k){
    int smallest_numer = std::limits::smallest;
    int m = v.size()/2;
    int der;
    int izq;
    vector<int> v_der(v.begin(), v.begin()+m);
    vector<int> v_izq(v.begin()+m, v.end());
    if (v.size() < k){
        return v[0];
    }else{
        der = getSmallestNumber(v_der, k);
        izq = getSmallestNumber(v_izq, k);
    }

}

/*************************************/
int main(){

    vector<int> v = {8,1,4,2,5,2};

    int SmallestNumber = getSmallestNumber(v,4);
    
    return 0;
}