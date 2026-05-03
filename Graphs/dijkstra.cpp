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

template<class T>
using minPQ = priority_queue<T, vector<T>, greater<>>;

vector<int> parent ;

vector<int> dijkstra(int src, int n, vector<vector<int>> &adj) {
    vector<int> dist(n+1, infi) ;
    parent.assign(n+1, -1) ;
    minPQ<pair<int,int>> pq;

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







