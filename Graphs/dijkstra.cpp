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


/*
cannot work with (-ve edges, negative cycles)

steps
maintain a 1D dist infi array & start node 0
maintain priority queue of(node, index, distance)
insert (s, 0) and loop while PQ ! empty
itrate over all childs and insert in PQ if can

*/

template<class T>
using minPQ = priority_queue<T, vector<T>, greater<>>;
// using maxPQ = priority_queue<T> ;

vector<int> parent ;

vector<int> dijkstra(int src, int n, vector<vector<pair<int,int>>> &adj) {
    parent.assign(n+1, -1) ;
    minPQ<pair<int,int>> pq;
    vector<int> dist(n+1, infi) ;

    dist[src] = 0 ;
    pq.emplace(0, src) ;

    while (!pq.empty()) {
        auto [cost, u] = pq.top() ;
        pq.pop() ;

        if (dist[u] < cost) continue;

        for (auto [v, w]: adj[u]) {
            if (dist[u] + w >= dist[v])continue;

            dist[v] = dist[u] +w;
            parent[v] = u;
            pq.emplace(dist[v] , v) ;
        }
    }
    return dist ;
}

vector<int> get_path(int src, int dest) {
    vector<int> path ;
    if (parent[dest] == -1 && src != dest)return path ;

    int cur = dest ;
    while (cur != -1) {
        path.push_back(cur) ;
        cur = parent[cur] ;
    }
    reverse(path.begin(), path.end());
    return path ;
}






// implementation of a nice problem 2D distance  https://codeforces.com/contest/1915/problem/G
template<class T>
using minPQ = priority_queue<T, vector<T>, greater<>>;
// using maxPQ = priority_queue<T> ;

vector<int> parent ;

vector<vector<int>> dijkstra(int src, int n, vector<vector<pair<int,int>>> &adj, vector<int> &ar) {
    parent.assign(n+1, -1) ;
    minPQ<array<int, 3>> pq;
    vector<vector<int>> dist(n+1, vector<int>(1001, infi)) ;
    vector<int> factors(n+1, infi);

    dist[src][ar[src]] = 0 ;
    pq.emplace( array<int,3>{0, ar[src] , src}) ;

    while (!pq.empty()) {
        auto [cost, factor,u] = pq.top() ;
        pq.pop() ;

        if (dist[u][factor] < cost) continue;

        for (auto [v, w]: adj[u]) {
            int newfactor = min(factor , ar[v]) ;
            if (dist[u][factor] + w*factor >= dist[v][newfactor] )continue;

            dist[v][newfactor] = dist[u][factor] + w*factor;
            parent[v] = u;
            pq.emplace(array<int,3>{dist[v][newfactor] , newfactor, v}) ;
        }
    }
    return dist ;
}
