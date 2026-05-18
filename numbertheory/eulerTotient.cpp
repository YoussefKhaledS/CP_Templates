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
int N = 5e7 , loog = 30;
using namespace std;
#define  int long long

vector<int> totient_1ton(int n) {// count # of int that is coprime with x -> gcd(x, int) = 1 O(nloglogn)
    vector<int> phi(n+1) ;

    for (int i = 0 ; i<= n ;i++)
        phi[i] = i ;

    for (int i =2 ; i<= n ;i++) {
        if (phi[i] == i) {
            for (int j = i ; j<=n ;j+=i) {
                phi[j]-=phi[j]/i ;
            }
        }
    }
    return phi ;
}

int toient(int n ) { // o(sqrt(n))
    int res = n ;

    for (int p = 2 ; p*p <= n;p++) {
        if (n% p == 0) {
            while (n% p == 0)
                n/=p;
            res -= res/p ;
        }
    }
    if (n > 1)res-=res/n ;

    return res;
}