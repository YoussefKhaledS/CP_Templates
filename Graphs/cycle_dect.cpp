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


vector<vector<int>> getcycle(vector<vector<int>> &adj) {
    int n = adj.size() ;
    vector<int> deg(n);
    vector<bool> del(n), vis(n);
    queue<int> q;

    for (int i =1 ; i< n ;i++) {
        deg[i] = adj[i].size() ;
        if (deg[i] <= 1)
            q.push(i), del[i]= 1;
    }

    while (!q.empty()) {
        int u = q.front(); q.pop() ;

        for (int v: adj[u])
            if (!del[v] && --deg[v] <= 1)
                q.push(v), del[v] =1 ;
    }


    vector<vector<int>> cycles ;

    for (int i =1 ; i < n ;i++) {
        if (del[i] || vis[i])continue;

        vector<int> cycle;
        int prv = -1 , u = i ;
        do {
            cycle.push_back(u) ;
            vis[u] = 1;

            int v = -1 ;
            for (int x: adj[u])
                if (!del[x] && x != prv) {
                    v = x ;
                    break;
                }
            prv = u ;
            u = v;
        }while (u != i);

        cycles.push_back(cycle);
    }

    return cycles;
}