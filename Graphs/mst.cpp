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
int N = 500002 , loog = 40;
using namespace std;
using namespace __gnu_pbds;
#define int long long
// #define int uint64_t
// #define u128 __uint128_t


/*
Time: O(M log N)
Memory: O(N + M)
 works on Weighted undirected graphs

The graph should be connected
    If the graph is connected, Prim produces one MST containing all N vertices.
    If the graph is disconnected, Prim starting from one node only visits its connected component. (you can make MS Forest)

the result is connected TREE with minimum sum of edges

The MST is not always unique
If all edge weights are distinct, the MST is unique

Negative * zero weights are completely fine

multiple and self loops are allowd

Kruskal with Disjoint Set Union steps

1- sort edges by increasing edge weight
2- initialize DSU for the graph
3- for each edge do a union find to merge them if the are diff

*/
struct DSU {
    vector<int> parent, sz;

    DSU(int n ) {
        parent.resize(n+1);
        sz.assign(n+1, 1) ;

        for (int i = 1; i <= n; i++)
            parent[i] =i;
    }

    int find(int x) {
        if (parent[x] == x)return x;
        return parent[x] = find(parent[x] );
    }

    void unite(int a, int b) {
        a = find(a) ;
        b = find(b) ;

        if (a== b)return ;

        if (sz[a] < sz[b])swap(a,b);

        parent[b]= a;

        sz[a]+=sz[b] ;
        return ;
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    int size(int x) {
        return sz[find(x)] ;
    }
};

struct Edge {
    int u,v , weight;
    bool operator<(Edge const& other) {
        return weight < other.weight; // to sort asc
    }
};
vector<vector<pair<int,int>>> mstAdj ;
int mstCost  ;
void mst(vector<vector<pair<int,int>>> &adj) {
    int n = adj.size();

    // step 1 createing the sorted edges array
    vector<Edge> edges;
    for (int node = 1 ; node < n ;node++) {

        for (auto [child, w] : adj[node]) {
            if (node < child)// because the adj is undirected and we need to store one edge
                edges.push_back({node, child, w}) ;
        }
    }
    sort(edges.begin(),edges.end());

    //step2 init the dsu
    DSU dsu(n) ;

    mstAdj.assign(n, {});
    int edgesCnt = 0;
    mstCost= 0 ;

    //step 3 kruskal
    for (auto [u, v, w]: edges) {
        if (dsu.same(u,v))continue;

        dsu.unite(u,v);

        mstAdj[u].push_back({v,w});
        mstAdj[v].push_back({u,w});

        mstCost+=w;
        edgesCnt++;

        if (edgesCnt == n-2)break;
    }
}