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

void solve()
{
    int n, k ;cin >> n >> k ;

    vector<int> ar(n) ;
    vector<vector<int>> need(n , vector<int>(64,0)) ;
    for (int i = 0 ; i < n; i++) {
        cin >> ar[i] ;
        bitset<64> x(ar[i]) ;

        for (int j = 0 ; j< 64;j++) {
            int y = ((1<<j+1) -1) ;

            int tmp = ar[i] & ((1<<j+1) - 1) ;
            need[i][j] = y - tmp ;
            cout << need[i][j] << ' ' ;
        }cout << el;
    }


}

signed main()
{

    youssef;
#ifndef ONLINE_JUDGE
    freopen("ts", "r", stdin);
#endif

    int ts = 1;

    // preprocess();

    // cin >> ts;
    for (int i = 1; i <= ts; i++)
    {
        solve();
        // cout << el;
    }
}