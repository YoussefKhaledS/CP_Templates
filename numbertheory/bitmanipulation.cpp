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
// int N = 5000002 , loog = 30;
using namespace std;
#define int long long


// find last left most set bit
int last(int x) {
    // base 64
    if (x <= 0)return -1 ;
    return 63 - __builtin_clzll(x) ;
    return 31 - __builtin_clz(x) ;
}

int count1(int x , int b) { // return number of 1s from 0 to x for a bit index
    int len = 1<<(b+1) ;
    int full = (x+1) / len ;
    int rem = (x+1) % len ;

    int ones = full * (1<<b) ;
    return ones+max(0ll, rem-(1<<b)) ;
}

int count1withsuffx(int x, int b, int pattern, int k) { // # of numbers n (0<=n<=x) such bit b in n is 1 and last k bits os n equal pattern
    if (x < pattern)return 0 ;

    int cnt = (x-pattern)/ (1ll<<k) +1 ;

    if (b < k)
        return ((pattern >> b) & 1)* cnt;

    b-=k;
    int len = 1ll << (b+1) ;
    return (cnt/len) * (1ll << b) + max(0ll, cnt% len - (1ll <<b)) ;
}