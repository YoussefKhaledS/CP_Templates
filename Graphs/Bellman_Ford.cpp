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

// Bellman-Ford: shortest distance from src
// Works with negative edges.
// Relax every edge n-1 times.
// dist[i] == infi => i is unreachable from src.
// n^2
//After k full iterations, Bellman-Ford has found the shortest paths using at most k edges.
// If one complete iteration makes no changes, you can stop.

struct Edge {
    int u,v,w ;
};
vector<int> bellmanford(int src, vector<Edge> &edges) {
    int n = adj.size();

    vector<int> dist(n, infi) ;
    dist[src] = 0 ;

    // for (int i = 1; i <= n-1 ;i++) {
    //     for (int u = 1 ; u <= n; u++) {
    //         if (dist[u] == infi)continue;
    //
    //         for (auto [v, w] : adj[u])
    //             dist[v] = min(dist[v] , dist[u]+w);
    //     }
    // }
    for (int i = 1; i< n; i++) {
        for (auto [u, v, w] : edges) {
            if (dist[u] == infi)continue;
            dist[v] = min(dist[v] , dist[u]+w);
        }
    }

    return dist ;
}

vector<int> ngcyclesstatus(vector<vector<pair<int,int>>> &adj, vector<int> &dist) {
    int n = adj.size();
    vector<int> status(n, 0 );

    // any node can still be relaxed is inside a ngcycle
    // if only for detection you can only run it once instead of n-1
    // do not forget the reachability of the node you are going to make in ngcycle
    // you should run the loop at least  1 if the n = 1
    for (int i = 1; i <= n-1 ;i++) {
        for (int u = 1 ; u <= n; u++) {
            if (dist[u] == infi)continue;

            for (auto [v, w] : adj[u])
                if (dist[u] + w < dist[v])// ngcycle
                    status[v] = 2 ;
        }
    }
    // if you want to find nodes that is affected from ngcycles just propagate from nodes with status 2

    return status ;
}


// get full ngcycle

struct Edge {
    int u,v,w ;
};
vector<int> getngcycle(int n ,int src, vector<Edge> &edges) {

    vector<int> dist(n, 0) ;
    vector<int> parent(n, 0) ;
    int x = -1 ;


    for (int i = 1; i<= n; i++) {
        x = -1 ;
        for (auto [u, v, w] : edges) {
            // if (dist[u] == infi)continue;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u]+w;
                parent[v] = u ;
                x=  v ;
            }
        }
    }
    if (x == -1)return {} ;

    // make sure x is inside cycle
    for (int i = 0 ; i< n;i++)x = parent[x] ;

    vector<int> cycle;
    int cur = x ;

    do {
        cycle.push_back(cur);
        cur = parent[cur] ;
    }while (cur != x);

    cycle.push_back(x);
    reverse(cycle.begin(), cycle.end());

    return cycle;
}






