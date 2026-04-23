#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define youssef                   \
    ios_base::sync_with_stdio(0); \
    cin.tie(0), cout.tie(0);
#define el '\n'
#define EL '\n'
#define ll long long
#define yes "YES"
#define no "NO"
const ll mod = 1e9 + 7, infi = LONG_MAX;
int N = 1e6+8;
using namespace std;
#define int long long


using namespace __gnu_pbds;

typedef tree<pair<int,int>, null_type, greater<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update> orderedset;
// find_by_order(k) : itrator of k-th smallest element
// order_of_key(x) : number of element less than x



void solve()
{
    orderedset os ;
    int id = 0 ;
    int ans = 0 ;
    int n; cin >> n ;
    for(int i = 0 ; i< n;i++){
        int x;cin >>x; 
        ans+= os.order_of_key({x, id+100}) ;
        os.insert({x, id++}) ;

        
    }
    // for(auto i : os)cout << i.first <<' ' << i.second<<el;

    cout << ans << el;

}

signed main()
{
    youssef;
    int ts = 1;
    

    cin >> ts;
    for(int i = 1 ; i<= ts ; i++)
    {
        solve();
        // cout << el;
    }
}