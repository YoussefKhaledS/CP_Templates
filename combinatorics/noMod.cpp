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
int N = 21 , loog = 40;
using namespace std;
using namespace __gnu_pbds;
#define int long long
// #define int uint64_t
#define u128 __uint128_t

long long fastPow(long long a, long long b) {
    long long res = 1;

    while (b) {
        if (b & 1)
            res *= a;

        a *= a;
        b >>= 1;
    }

    return res;
}

vector<long long> fact(N + 1);

void buildfactorial(int n) {
    fact[0] = 1;

    for (int i = 1; i <= n; i++)
        fact[i] = fact[i - 1] * i;
}

long long nPr(int n, int k) {
    // nPr = n! / (n-k)!
    if (k > n)
        return 0;

    return fact[n] / fact[n - k];
}

long long nCr(int n, int r) {
    if (r > n || r < 0)
        return 0;

    return fact[n] / (fact[r] * fact[n - r]);
}

// Derangement:
// D[n] = (n - 1) * (D[n - 1] + D[n - 2])
// D[0] = 1, D[1] = 0
vector<long long> derangements(int n) {
    vector<long long> d(n + 1);

    d[0] = 1;
    if (n >= 1)
        d[1] = 0;

    for (int i = 2; i <= n; i++)
        d[i] = (i - 1) * (d[i - 1] + d[i - 2]);

    return d;
}


void solve() {
    int n ;cin >> n;

    int ans = nCr(n, n/2) /2 ;
    ans*= fastPow(fact[n/2 -1], 2);

    cout << ans;
}

signed main()
{

    youssef;
#ifndef ONLINE_JUDGE
    freopen("ts", "r", stdin);
#endif

    int ts = 1;

    // preprocess();
    buildfactorial(N) ;
    // cin >> ts;
    for (int i = 1; i <= ts; i++)
    {
        // cout << "Case "<< i << ": " ;
        solve();
        // solve2() ;
        cout << el;
    };
}