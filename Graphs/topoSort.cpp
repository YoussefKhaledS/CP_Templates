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
const ll mod = 1e9+7 , infi = 1e17;
int N = 1e5 + 4 , loog = 60;
using namespace std;
// #define int long long


/*
 * Kahn's Algorithm (BFS)
 * Start from nodes with indegree = 0.
 * Remove them one by one, decreasing the indegree of their neighbors.
 * If all n nodes are processed, the graph is a DAG and 'topo' is a valid topological order.
 */
vector<int> topoSort(vector<vector<int>> &adj) {
    int n = adj.size() -1 ;
    vector<int> indeg(n+1), topo ;
    queue<int> q;

    for (int u = 1 ; u <= n;u++)
        for (int v : adj[u])
            indeg[v]++;

    for (int i = 1 ; i<=n ;i++)
        if (indeg[i]==0)
            q.push(i) ;

    while (!q.empty()) {
        int u = q.front() ; q.pop() ;
        topo.push_back(u);

        for (int v : adj[u])
            if (--indeg[v] == 0)
                q.push(v);

    }
    return topo;
}