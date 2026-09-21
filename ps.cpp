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
int N = 7e5+3, loog = 40;
using namespace std;
using namespace __gnu_pbds;
#define int long long
// #define int uint64_t
// #define u128 __uint128_t
// todo convert dfs->bfs easly
// todo equations of the all summation ex:i*(i+1)/2



struct Trie {
    int LOG = 40 ;
    int k ;
    struct Node {
        int nxt[2]; // store the index of the child node from using char i
        int pref;// number of inserted strings having this prefix

        Node() {
            memset(nxt, -1, sizeof nxt) ;
            pref= 0 ;
        }
    };

    vector<Node> tree;

    Trie(int _k) {
        tree.push_back(Node());// root node
        k = _k ;
    }

    void insert(int n) {
        int cur = 0 ; //start at the root node

        for (int i = LOG; i>= 0 ;i--){
            int bit = (1ll<<i) & n ;
            bool on = bit ;

            if (tree[cur].nxt[on] == -1) {
                tree[cur].nxt[on] = tree.size() ;// the index of the node we will add
                tree.push_back(Node()); // the newly added node
            }

            cur = tree[cur].nxt[on];
            tree[cur].pref++;
        }
    }

    int maxxor(int x) {
        int cur = 0 ;
        int ans = 0 ;

        for (int i = LOG ;i >= 0 ;i--) {
            int bit = (1ll<<i) & x ;
            bool on = bit ;

            if (ans >= k) {
                return tree[cur].pref;
            }
            int nxtcurx = tree[cur].nxt[!on] ;
            int nxtcury = tree[cur].nxt[on] ;


            if (nxtcurx != -1 && tree[nxtcurx].pref != 0) {
                ans|=(1ll << i);
                cur = nxtcurx;
            }else {
                cur = nxtcury ;
            }
        }
        if (ans >= k) {
            return tree[cur].pref;
        }else return 0;
    }
};


void solve() {

    int n , k ;cin >> n >> k ;

    vector<int> ar(n+1) , prfix(n+1, 0 );
    for (int i = 1 ; i <= n; i++) {
        cin >> ar[i] ;
        prfix[i] = ar[i] ^ prfix[i-1] ;
    }

    Trie trie(k);
    int ans= 0 ;
    trie.insert(0);

    for (int i = 1 ; i<= n;i++){
        int x = prfix[i] ;

        cout << trie.maxxor(x) <<el ;
        ans+= trie.maxxor(x);
        trie.insert(x);
    }
    cout << ans ;


}

void preprocess() {

    // buildfactorial(N) ;
    // buildSPF(N-1) ;
}


signed main()
{

    youssef;
#ifndef ONLINE_JUDGE
    freopen("ts", "r", stdin);
#endif

    int ts = 1;

    preprocess();

    // cin >> ts;
    for (int i = 1; i <= ts; i++)
    {
        // cout << "Case "<< i << ": " ;
        solve();
        // solve2() ;
    };
}