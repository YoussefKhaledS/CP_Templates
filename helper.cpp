#include <iostream>
#include <vector>
#include <algorithm>
#include <functional> // For std::greater
#include <bits/stdc++.h>
using namespace std; 

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

int main() {
    vector<int> divs = num_of_divisors(1e6) ;

    cout << divs[6] ;
    
}