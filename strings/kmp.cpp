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

// prefix/failure function -> what is the longest proper prefix of S[0..i] that is also a suffix
// pi[] as a precomputed array that tells you how much of the string you can reuse after a mismatch.

vector<int> failure_function(string s) {
    int n = s.size() ;
    vector<int> lps(n, 0) ;

    for (int i = 1; i< n; i++) {
        int j = lps[i-1];// j is the length of the prefix that we think = suffix

        while (j > 0 && s[i] !=s[j])
            j = lps[j-1] ;

        if (s[i] == s[j])
            j++;

        lps[i] = j ;
    }
    return lps;
}















