#include <iostream>
#include <vector>
#include <algorithm>
#include <functional> // For std::greater
#include <bits/stdc++.h>
using namespace std; 
long long mod = 1e9+7 ;

vector<int> int_to_binary(int x, int n = 30){
    vector<int> bits(n);
    for(int i =0 ; i< n; i++){
        bits[i] = (x >> i) & 1;
    }
    return bits;
}

int binary_to_int(vector<int> &bits){
    int x = 0 ;
    for(int i = 0 ; i< bits.size() ;i++){
        if(bits[i])
            x |= (1<<i);
    }
    return x ;
}

vector<int> num_of_divisors(int n){
    vector<int> divs(n,0) ;

    for(int i =1 ; i< n ;i++){
        for(int j = i; j < n ;j+=i){
            divs[j]++;
        }
    }
    return divs;
}

void coordinate_compression(){
    vector<int> all ;// vector that have every thing 

    sort(all.begin() , all.end()) ;
    all.erase(unique(all.begin() , all.end()), all.end()) ;// to remove dublicates
    auto m = [&](int x){
        return lower_bound(all.begin() , all.end(), x) - all.begin()  ;
    };
}

// operations under modulo
int addm(int &a, int &b) {
    return (a%mod + b%mod)%mod;
}
int multm(int &a, int &b) {
    return (a%mod * b%mod)%mod;
}

vector<int> stringtovector(string &s) {// lowercase english letters
    vector<int> res ;

    for (char c : s)
        res.push_back(c - 'a');

    return res ;
}
string vectortostring(vector<int> ar) {// lower case english letters
    string s ;
    for (int x : ar) {
        s.push_back(x + 'a') ;
    }
    return s;
}
int main() {

    cout << 'z' - 'a' ;



    
}