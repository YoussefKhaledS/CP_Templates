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

int fastPow(int a,int b) {
    int res =1 ;
    while (b) {
        if (b&1)res*=a;
        res%= mod;

        a*=a;
        a%=mod;
        b>>=1;
    }
    return res % mod;
}

int modinverse(int x) {
    return fastPow(x, mod-2) ;
}

int modDivide(int x, int y) {
    return x * modinverse(y) %mod;
}

vector<int> fact(N+1) ;
void buildfactorial(int n) {
    fact[0] =1 ;
    for (int i =1 ;i <= n ; i++) {
        fact[i] = (fact[i-1] * i) %mod ;
    }
}

int nPr(int n, int k) {// nPr number of permuts using only k ele from n ele
    // n!/(n-k)!
    if (k>n)return 0 ;
    return fact[n] * modinverse(fact[n-k]) %mod ;
}

// ncr = (n-1)Cr + (n-1)C(r-1) Pascal's identity    think about take or leave
int nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    return 1LL * fact[n]
           * modinverse(fact[r]) % mod
           * modinverse(fact[n-r]) % mod;
}
int nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    return 1LL * nPr(n, r) * modinverse(fact[r]) % mod;
}

int nCr(int n , int r ) {// manual way
    int ans =1 ;

    for (int i =1 ; i<= r ;i++)
        ans = ans*(n-i +1) /i ;

    return ans ;
}

int nPr(int n, int r) {// manual way

    int ans =1 ;
    for (int i = 0 ;i < r ;i++)
        ans*=(n-i) ;

    return ans ;
}







