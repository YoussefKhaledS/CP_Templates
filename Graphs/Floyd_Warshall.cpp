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

struct Floyd {
    vector<vector<int>> dist;// shortest path u -> v
    vector<vector<int>> nxt ;// next vertex on shortest path u->v
    bool ngcycle = false ;
};

Floyd floydwarshall(int n, vector<vector<pair<int,int>>> &adj) {

    Floyd res ;n++;
    vector<vector<int>> &dist = res.dist;
    vector<vector<int>> &nxt = res.nxt ;
    bool &ngcycle = res.ngcycle ;
    dist.assign(n, vector<int>(n,infi)) ;
    nxt.assign(n, vector<int>(n, -1)) ;

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
    // ngative cycle exist if dist[i][i] < 0
    for (int i = 0 ; i < n;i++)
        if (dist[i][i] < 0) {
            ngcycle = true;
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