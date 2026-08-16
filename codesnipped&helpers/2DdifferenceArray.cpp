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
const ll mod = 998244353 , infi = 1e18;
int N = 5000002 , loog = 30;
using namespace std;
#define int long long


int  n, m;

vector<vector<int>> diff(100+2, vector<int>(100+2,0)) ;
void update(int x1, int y1, int x2, int y2, int v) {
    diff[x1][y1]+=v;
    diff[x1][y2 + 1]-=v;
    diff[x2+1][y1]-=v;
    diff[x2 + 1][y2 +1]+=v;
}
// after updates:
void after_updates() {
    for (int i = 1 ; i <= n;i++) {
        for (int j = 1 ; j <= m ;j++) {
            // up + left - (upper left)
            diff[i][j] += diff[i-1][j] + diff[i][j-1] - diff[i-1][j-1] ;
            // cout << diff[i][j] << ' ';
        }
        // cout <<el;
    }
}

/*
0  0   0   0   0   0  0
0  0  10   0   0 -10  0
0  0   0   0   0   0  0
0  0 -10   0   0  10  0
0  0   0   0   0   0  0
 */

// Recognition pattern
// Whenever you see:
//
// people entering/leaving
// trains arriving/departing
// rooms occupied
// servers active
// customers in a store
// jobs running
// intervals overlapping

/*
G. Range update + point query, but ONLINE?

Think:

Difference Array + Fenwick Tree
H. Range update + range sum, ONLINE?

Think:

Fenwick × 2

or

Lazy Segment Tree
 */
signed main() {
    n = 5 ;
    m = 7 ;

    update(2,3, 4,6 , 10) ;
    update(1,2,3,5 ,3);

    after_updates();


}