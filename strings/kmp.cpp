//
// Created by ykhaled on 9/15/2026.
//
#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define youssef ios_base::sync_with_stdio(0); cin.tie(0), cout.tie(0);
#define el '\n'
#define EL '\n'
#define yes "YES"
#define no "NO"
#define ll long long
const ll mod = 1e9 + 7 , infi = 1e17;
int N = 7e5+3, loog = 40;
using namespace std;
using namespace __gnu_pbds;
#define int long long


vector<int> failure_function(string s) {
    int n = s.size() ;
    vector<int> ar(n) ;

    for (int i = 1; i< n; i++) {
        int j = ar[i-1];

        while (j > 0 && s[i] !=s[j])
            j = ar[j-1] ;

        if (s[i] == s[j])
            j++;

        ar[i] = j ;
    }
    return ar;
}














