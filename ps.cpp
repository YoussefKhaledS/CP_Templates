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
int N = 5000002 , loog = 40;
using namespace std;
using namespace __gnu_pbds;
#define int long long
// #define int uint64_t

void solve() {

    int n ;cin >> n ;

    vector<array<int ,3>> ar(n) ;
    for (int i = 0 ; i< n; i++) {
        int x, h ;cin >> x >> h;
        ar[i] = {x, h , i};
    }
    sort(ar.begin(), ar.end()) ;

    vector<int> dp(n+1, 1) ;

    for (int i = n - 2 ; ~i ; i--) {
        auto [x,h, ii] = ar[i] ;



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
        // solve2() ;
        cout << el;
    }
}