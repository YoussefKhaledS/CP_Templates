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
int N = 21 , loog = 40;
using namespace std;
using namespace __gnu_pbds;
#define int long long
// #define int uint64_t
#define u128 __uint128_t

// The height of every subtree attached to the diameter is <= its distance to the nearest diameter endpoint.
// you need to try it first CANNOT intuition
// mostly if you will use it you need to ignore the rest of the subtrees based on the first comment

void getFarthestDFS(int node, int parent, vector<vector<int>> &adj, int dist, int &farthest, int &maxDist, vector<int> &parents) {
    if (dist > maxDist) {
        maxDist = dist;
        farthest = node ;
    }

    for (int child : adj[node]) {
        if (child == parent)continue;

        parents[child] = node ;
        getFarthestDFS(child , node, adj, dist + 1, farthest, maxDist, parents);
    }
}

vector<int> getDiameter(vector<vector<int>> &adj) {
    int n = adj.size() ;

    vector<int> parents(n, -1) ;

    int a, b;
    int maxDist = -1 ;

    // find first endpoint assuming 0 is a node
    getFarthestDFS(0, -1, adj, 0, a , maxDist, parents);

    // find second endpoint
    fill(parents.begin(),parents.end(), -1);
    maxDist = -1;

    getFarthestDFS(a, -1, adj, 0, b , maxDist, parents);

    // build diameter
    vector<int> diameter ;

    for (int node = b ; node != -1; node = parents[node]) {// because a acts as the root of the tree now
        diameter.push_back(node) ;
    }
    reverse(diameter.begin(), diameter.end()) ;

    return diameter;
}


signed main()
{

}



// another implementation
const int N = 2e5 + 9;

vector<int> g[N];
int farthest(int s, int n, vector<int> &d) {
    static const int inf = N;
    d.assign(n + 1, inf); d[s] = 0;
    vector<bool> vis(n + 1);
    queue<int> q; q.push(s);
    vis[s] = 1; int last = s;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v: g[u]) {
            if (vis[v]) continue;
            d[v] = d[u] + 1;
            q.push(v); vis[v] = 1;
        }
        last = u;
    }
    return last;
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> dx, dy;
    int x = farthest(1, n, dx);
    int y = farthest(x, n, dx);
    farthest(y, n, dy);
    for (int i = 1; i <= n; i++) {
        cout << max(dx[i], dy[i]) << ' ';
    }
    cout << '\n';
    return 0;
}
