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

struct BFS {
    int n;
    vector<vector<int>> adjlist ;
    vector<int> dist, vis, parent;

    BFS(int nodes) {
        n = nodes;
        adjlist.assign(n+1, {} );
        dist.assign(n+1, infi);
        vis.assign(n+1, 0);
        parent.assign(n+1, -1);
    }

    void add_edge(int u,int v) {
        adjlist[u].push_back(v) ;
        adjlist[v].push_back(u) ;
    }

    void bfs(int src) {
        queue<int> q;

        vis[src] = 1;
        dist[src] = 0 ;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (auto child : adjlist[node]) {
                if (vis[child])continue;

                vis[child] = 1;
                dist[child] = dist[node]+1;
                parent[child] = node;
                q.push(child) ;
            }
        }
    }
};