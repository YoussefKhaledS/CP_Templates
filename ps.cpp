#include <iostream>
// #include <bits/stdc++.h>
#include <vector>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
#define youssef ios_base::sync_with_stdio(0); cin.tie(0), cout.tie(0);
#define el '\n'
#define EL '\n'
#define yes "YES"
#define no "NO"
#define ll long long
const ll mod = 998244353 , infi = 1e18;
int N = 5000002 , loog = 30;
using namespace std;
#define int long long

vector<vector<int>> dp ;

int dfs(int idx , int rem, vector<int> &ar , vector<int> &price) {
    if (rem <= 0)return 0 ;

    if (idx < 0)return infi;

    if (dp[idx][rem] != -1)return dp[idx][rem] ;

    int ret = infi ;
    for (int i = 1 ; i <= min(ar[idx] , rem) ; i++) {
        ret = min(ret , dfs(idx -1 , rem-i , ar, price) + (i+10) * price[idx]) ;
    }

    return dp[idx][rem]= ret ;
}



void solve() {
    int n ;cin >> n ;

    vector<int> ar(n) , prefx(n) , price(n) ;
    for (int i =0 ; i< n;i++) {
        cin >> ar[i] >> price[i] ;

        prefx[i] = (i == 0)? ar[i] : ar[i] + prefx[i-1] ;
    }
    dp.assign(n , vector<int>(prefx[n-1] + 1 , -1)) ;
    cout << dfs(n-1, prefx[n-1] , prefx, price) << el ;
}

signed main()
{

    youssef;
#ifndef ONLINE_JUDGE
    freopen("ts", "r", stdin);
#endif

    int ts = 1;

    // preprocess();

    cin >> ts;

    for (int i = 1; i <= ts; i++)
    {
        solve();
        // cout << el;
    }
}