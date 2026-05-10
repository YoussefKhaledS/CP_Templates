/*
 *case processing and batch processing is not included unditll now
 */


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
#define int long long
int sq = 350 ;
vector<int> mn(sq , 1e8) ;

void solve()
{
    int n ;cin >> n ;
    vector<int> ar(n) ;
    for (int i = 0 ; i< n; i++) {
        cin >> ar[i] ;
        mn[i/sq] = min(mn[i/sq] , ar[i] ) ;
    }

    int q ;cin >> q ;
    while (q--) {
        int l ,r ; cin >> l >> r;
        int ans = 1e9 ;

        while (l <= r && l% sq != 0 ) {
            ans = min(ans , ar[l++]) ;
        }

        while (l+sq -1 <= r) {
            ans = min(mn[l/sq], ans)  ;
            l+=sq;
        }
        while (l <= r ) {
            ans = min(ans, ar[l++]) ;
        }
        cout << ans <<el ;

    }
}
