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
const ll mod = 1e9 + 7, infi = LONG_MAX;
int N = 500002, loog = 30;
using namespace std;
#define int long long

/*
 *For any dp solution you need those and you can make recursion | itrative
 * 1- state
 * 2- dp difinition
 * 3- transition
 * 4- base case
 *
 *----------------
 * if you detect a cycle in the dp its wrong
 * cycle is that you can reach to the same state | your state solution can depend on your same state solution again
 *
 * -------------
 *
 * if you have for example cost that is in the state start from it to the 0
 *
 * you can treate the dp call as o(1) if you did not clear the memo array
 *
 * ---------
 */

int dfs(int mask, int &n, vector<unordered_set<int>> &adj) {
    if (mask == (1<<(n+1))-1)return 0 ;

    int &ret = dp[mask] ;
    if (ret != -1)return ret ;
    ret = infi ;

    int full = (1<<(n+1))-1 ;
    int rem = full ^ mask;

    for (int sub = rem ; sub ; sub = (sub -1 ) & rem) {
        if (check(sub, adj, n)) {
            ret = min(ret , 1+dfs(mask | sub , n , adj )) ;
        }
    }
    // for (int i = 2 ; i < (1<<(n+1)) ; i++) {
    //     if ((mask & i) == 0 && check(i, adj, n)) {
    //         ret = min(1+dfs(mask | i, n , adj), ret )  ;
    //     }
    // }

    return ret ;
}