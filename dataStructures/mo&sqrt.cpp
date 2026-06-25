#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define youssef ios_base::sync_with_stdio(0); cin.tie(0), cout.tie(0);
#define el '\n'
#define EL '\n'
#define yes "Yes"
#define no "No"
#define ll long long
const ll mod = 1e9 + 7 , infi = 1e17;
int N = 5000002 , loog = 40;
using namespace std;
#define int long long

struct Query {
    int l , r , idx;
};

struct Mo {
    int n, sq, ans;
    vector<int> ar ;
    vector<int> freq ;
    Mo(vector<int> &v, int q) {
        ar = v ;
        n = v.size() ;
        sq = sqrt(n) +1 ;
        ans = 0 ;
    }

    void add(int idx) {

    }
    void del(int idx) {

    }

    void solve(vector<Query> &q) {
        sort(q.begin(), q.end(), [&](auto &lf, auto &ri) {
            if (lf.l / sq == ri.l / sq)
                return (lf.l / sq) & 1 ? lf.r > ri.r : lf.r < ri.r ;

            return lf.l / sq < ri.l / sq ;
        });

        int l = q[0].l, r = q[0].l ;
        add(l) ;

        vector<int> res(q.size() );
        for (auto [lq, rq, idx] : q) {
            while (r < rq) add(++r) ;
            while (l < lq) del(l++) ;
            while (l > lq) add(--l) ;
            while (r > rq) del(r--) ;

            res[idx] = ans ;
        }

        for (int i = 0; i < res.size() ; i++) {
            cout << res[i] << el;
        }

    }
};