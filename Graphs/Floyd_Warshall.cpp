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

// dp[i][j] = shortest path from i to j using only vertices [0 ... k]
// Base case k = -1: only direct edges (and i -> i = 0) are allowed.

// Transition:
// Either the shortest i -> j path does NOT use k:
//      dp[i][j]
// Or it uses k:
//      dp[i][k] + dp[k][j]
// So:
//      dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j])
// Base case: shortest path using no intermediate vertices.
// Direct edge i -> j, or 0 if i == j, otherwise INF.

struct Floyd {
    vector<vector<int>> dist;// shortest path u -> v
    vector<vector<int>> nxt ;// next vertex on shortest path u->v
    vector<int> ngstate;
    // 0 = not affected by ngcycle
    // 1 = affected
    // 2 = inside ngcycle
    bool ngcycle = false ;
};

Floyd floydwarshall(int n, vector<vector<pair<int,int>>> &adj) {

    Floyd res ;n++;
    vector<vector<int>> &dist = res.dist;
    vector<vector<int>> &nxt = res.nxt ;
    bool &ngcycle = res.ngcycle ;
    dist.assign(n, vector<int>(n,infi)) ;
    nxt.assign(n, vector<int>(n, -1)) ;
    res.ngstate.assign(n, 0) ;

    for (int i = 0 ; i< n;i++) {
        dist[i][i] = 0 ;
        res.nxt[i][i] = i ;

        for (auto [v, w]: adj[i]) {
            if (w < dist[i][v]) {
                dist[i][v] = w ;
                nxt[i][v] = v;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0 ; i<n ;i++) {
            for (int j = 0 ; j < n; j++) {
                if (dist[i][k] == infi || dist[k][j] == infi)continue;

                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j] ;
                    nxt[i][j] = nxt[i][k] ;
                }
            }
        }
    }

    // dist[k][k] < 0   -->  k is involved in a negative cycle
    for (int k = 0 ; k < n;k++) {
        if (dist[k][k] >= 0)continue;

        res.ngcycle = true;
        res.ngstate[k] = 2 ;


        //i can reach the negative cycle through k
        //j can be reached from the negative cycle through k
        for (int i = 0 ; i < n;i++) {
            if (dist[i][k] == infi)continue;

            for (int j = 0 ; j < n; j++) {
                if (dist[k][j] == infi)continue;

                if (res.ngstate[i] == 0)res.ngstate[i] =1 ;
                if (res.ngstate[j] == 0)res.ngstate[j] =1 ;
            }
        }
    }
    return res ;
}

vector<int> getpath(int src, int dist, vector<vector<int>> &nxt) {
    if (nxt[src][dist] == -1)return {} ;

    vector<int> path ;
    while (src != dist) {
        path.push_back(src);
        src = nxt[src][dist] ;
    }

    path.push_back(dist);
    return path ;
}