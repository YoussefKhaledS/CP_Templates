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
int N = 5e5 , loog = 30;
using namespace std;
#define  int long long
using u128 = __uint128_t ;

int mulmod(int a, int b, int mod) {
    return (u128)a*b %mod;
}

int binpow(int a, int b, int mod) {
    int res =1 ;

    while (b) {
        if (b &1)
            res = mulmod(res, a , mod) ;

        a= mulmod(a,a,mod) ;
        b>>=1;
    }
    return res ;
}

bool isPrime(int n) {
    if (n < 2)
        return false ;

    for (int p: {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if (n%p == 0)
            return n== p ;
    }

    int d = n -1 ;
    int s =0 ;

    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int a : {2, 325,9375,28178,450775,9780504,1795265022}) {
        if (a%n == 0)
            continue;

        int x = binpow(a, d , n);

        if (x == 1 || x == n-1)
            continue;

        bool comp = true;

        for (int r =1 ; r < s ; r++) {

            x = mulmod(x,x,n) ;
            if (x == n-1) {
                comp = false ;
                break;
            }
        }

        if (comp)
            return false ;
    }
    return true;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()) ;

int pollard(int n) {
    if (n%2 == 0)
        return 2 ;

    if (n%3 == 0)
        return 3 ;

    int c = uniform_int_distribution<int>(1, n-1 )(rng) ;
    int x = uniform_int_distribution<int>(0, n-1)(rng);
    int y = x ;

    auto f = [&](int x) {
        return (mulmod(x,x,n) + c) %n;
    };

    while (true) {

        x = f(x) ;
        y = f(f(y)) ;

        int d = gcd(abs(x - y), n) ;

        if (d ==1)
            continue;

        if (d ==n)
            return pollard(n) ;

        return d ;
    }
}

void factor(int n, vector<int> &fac) {
    if (n ==1)
        return;

    if (isPrime(n)) {
        fac.push_back(n);
        return;
    }

    int d = pollard(n) ;

    factor(d, fac) ;
    factor(n/d, fac) ;
}

vector<int> prime_factorization(int n) {

    vector<int> fac;
    factor(n , fac);

    sort(fac.begin() , fac.end()) ;
    return fac;
}

signed main() {
    int n ;cin >> n ;
    vector<int> a = prime_factorization(n) ;
    for (auto i : a)cout << i << ' ' ;
}





