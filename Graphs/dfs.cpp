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

struct DFS {
    int n;
    vector<vector<int>> adjlist ;
    vector<int> vis, depth, parent, subtree;

    DFS(int nodes) {
        n = nodes;
        adjlist.assign(n+1, {}) ;
        vis.assign(n+1, 0);
        depth.assign(n+1, 0) ;
        parent.assign(n+1, -1);
        subtree.assign(n+1, 0) ;
    }
    void add_edge(int u, int v) {
        adjlist[u].push_back(v) ;
        adjlist[v].push_back(u) ;
    }

    void dfs(int node, int par = -1) {
        vis[node] = 1;
        parent[node] = par;
        subtree[node] = 1;

        for (auto child: adjlist[node]) {
            if (child != par) {
                depth[child] = depth[node]+1 ;
                dfs(child, node) ;
                subtree[node]+=subtree[child] ;
            }
        }
    }
};