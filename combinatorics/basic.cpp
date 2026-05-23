#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define youssef ios_base::sync_with_stdio(0); cin.tie(0), cout.tie(0);
#define el '\n'
#define EL '\n'
#define yes "YES"
#define no "NO"
#define ll long long
const ll mod = 998244353 , infi = LONG_MAX;
int N = 5000002 , loog = 30;
using namespace std;
#define int long long

int fastpow(int a,int b) {
    int res =1 ;
    while (b) {
        if (b&1)res*=a;

        a*=a;
        b>>=1;
    }
    return res;
}

int modinverse(int x) {
    return fastPow(x, mod-2) ;
}

vector<int> fact(N+1) ;
void buildfactorial(int n) {
    fact[0] =1 ;
    for (int i =1 ;i <= n ; i++) {
        fact[i] = (fact[i-1] * i) %mod ;
    }
}

int permutations(int n, int k) {// number of permuts using only k ele from n ele
    // n!/(n-k)!
    if (k>n)return 0 ;
    return fact[n] * modinverse(fact[n-k]) %mod ;
}









