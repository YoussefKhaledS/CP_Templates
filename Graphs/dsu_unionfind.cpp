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
const ll mod = 1e9 + 7 , infi = 1e17;
int N = 5000002 , loog = 40;
using namespace std;
using namespace __gnu_pbds;
#define int long long

struct DSU {
    vector<int> parent, sz;

    DSU(int n ) {
        parent.resize(n+1);
        sz.assign(n+1, 1) ;

        for (int i = 1; i <= n; i++)
            parent[i] =i;
    }

    int find(int x) {
        if (parent[x] == x)return x;
        return parent[x] = find(parent[x] );
    }

    void unite(int a, int b) {
        a = find(a) ;
        b = find(b) ;

        if (a== b)return ;

        if (sz[a] < sz[b])swap(a,b);

        parent[b]= a;

        sz[a]+=sz[b] ;
        return ;
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    int size(int x) {
        return sz[find(x)] ;
    }
};