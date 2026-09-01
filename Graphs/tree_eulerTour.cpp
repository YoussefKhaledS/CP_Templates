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
int N = 2e5+3, loog = 40;
using namespace std;
using namespace __gnu_pbds;
// #define int long long
// #define int uint64_t
// #define u128 __uint128_t


// todo euler tour to get subtree queries

int timer =0;
vector<vector<int>> adj(N) ;
vector<int> tin(N), tout(N), flat_subtree(N) ;
// the flat array should contain index 0->n-1 only
// this flat array indexis is only the tin for each node
// the tin to tout represent the subtree starting from node

void dfs(int node, int parent) {

    tin[node] = timer;

    flat_subtree[timer] = node; // you can make another array with the value for example to subtree queries

    for (int child : adj[node]) {
        if (child == parent)continue;
        timer++;
        dfs(child, node);
    }

    tout[node] = timer ;
}

// is child inside node's subtree or is node ansesstor for child
bool isInSubtree(int node, int child ) {
    return tin[node] < tin[child] && tin[child] <= tout[node] ;
}

// todo euler tour to get path queries

int timer =0;
vector<vector<int>> adj(N) ;
vector<int> tin(N), tout(N), flat_path(2*N) ;
// the flat array should contain index 0->2*n-1 only
void dfs(int node, int parent) {
    tin[node] = timer ;

    flat_path[timer++] = node ;

    for (int child : adj[node]) {
        if (child == parent)continue;

        dfs(child, node);
    }

    tout[node] = timer ;
    flat_path[timer++] = -node; // to remvove it from the path
}

// is child inside node's subtree or is node ansesstor for child
bool isInSubtree(int node, int child ) {
    return tin[node] <= tin[child] && tin[child] < tout[node] ;
}


