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
// #define int uint64_t
// #define u128 __uint128_t
// todo convert dfs->bfs easly
// todo equations of the all summation ex:i*(i+1)/2
pair<int,int> ky(int a, int b) {
    return {max(a,b), min(a,b)};
}
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
    int u,v , weight, j;
    bool operator<(Edge const& other) {
        return weight < other.weight; // to sort asc
    }
};
vector<vector<pair<int,int>>> mstAdj ;
int mstCost  ;
vector<bool> vis(N, 0);
vector<Edge> edges;

void mst(int n) {

    // step 1 createing the sorted edges array

    sort(edges.begin(),edges.end());

    //step2 init the dsu
    DSU dsu(n) ;

    mstAdj.assign(n, {});
    int edgesCnt = 0;
    mstCost= 0 ;

    //step 3 kruskal
    for (auto [u, v, w, j]: edges) {
        if (dsu.same(u,v))continue;

        dsu.unite(u,v);
        vis[j] = 1 ;

        mstAdj[u].push_back({v,w});
        mstAdj[v].push_back({u,w});

        mstCost+=w;
        edgesCnt++;

        if (edgesCnt == n-2)break;
    }
}

struct LCA
{
    int **memo, log;
    vector<vector<pair<int,int>>> adjlist ;
    vector<int> lev;

    LCA(int n, vector<vector<pair<int,int>>> &_adjlist, int root)
    {
        adjlist = _adjlist;
        memo = new int *[n + 1];
        log = (int)ceil(log2(n));
        lev.assign(n+1 , 0) ;
        for (int i = 0; i <= n; i++)
        {
            memo[i] = new int[log+1];
        }

        build(root, root);
    }

    void build(int u, int p)
    {
        memo[u][0] = p;

        for (int i = 1; i <= log; i++)
            memo[u][i] = memo[memo[u][i - 1]][i - 1];

        for (auto [v,c] : adjlist[u])
        {
            if (v != p)
            {
                lev[v] = lev[u] + 1;
                build(v, u);
            }
        }
    }

    int get(int u, int v)
    {
        // u is the farthest from the root
        if (lev[u] < lev[v])
            swap(u, v);

        // making u at the same level of v
        for (int i = log; i >= 0; i--)
        {
            if ((lev[u] - (1 << i)) >= lev[v])
            {
                u = memo[u][i];
            }
        }
        // here v was originally the ancestor of u
        if (u == v)
            return v;

        // finding the node closest to the root which is not the common ancestor
        for (int i = log; i >= 0; i--)
        {
            if (memo[u][i] != memo[v][i])
            {
                u = memo[u][i];
                v = memo[v][i];
            }
        }
        return memo[u][0];
    }

    int kth(int u , int k){
        assert(k >= 0) ;
        for(int i = 0 ; i<= log;i++){
            if(k& (1<<i)){
                u = memo[u][i] ;
            }
        }
        return u ;
    }

    int dist(int u, int v){
        int l = get(u, v);
        return lev[u]+ lev[v] - 2 * lev[l] ;
    }

    int go(int u, int v, int k){
        int l = get(u,v) ;

        int dist_u_l = lev[u] - lev[l] ;

        // still going up from u to lca
        if(k <= dist_u_l){
            return kth(u,k) ;
        }

        // go down from lca to v
        k -= dist_u_l;

        int dist_v_l = lev[v] - lev[l] ;
        return kth(v, dist_v_l - k) ;
    }

};
map<pair<int,int>, int> mp ;
int timer =0;
vector<int> tin(N), tout(N), flat_path(2*N) ;
// the flat array should contain index 0->2*n-1 only
void dfs(int node, int parent) {
    tin[node] = timer ;

    flat_path[timer++] = mp[ky(node, parent)] ;

    for (auto [child,w] : mstAdj[node]) {
        if (child == parent)continue;

        dfs(child, node);
    }

    tout[node] = timer ;
    flat_path[timer++] = -mp[ky(node, parent)]; // to remvove it from the path
}

struct ST{
    vector<vector<int>> memo ;
    vector<int> logs;

    int merge(int &lf, int &ri)
    {
        return max(lf, ri);
    }

    ST(vector<int> &ar){
        int n = ar.size();
        logs.assign(n+1 , 0) ;

        //building logs for fast access
        for(int i = 2; i<= n ;i++)logs[i] = logs[i/2] +1 ;

        memo.assign(logs[n] + 1 , vector<int>(n)) ;
        memo[0] = ar;

        for(int i = 1; i <= logs[n];i++){
            int l = 1 << i ;
            for(int j = 0 ; j+l <= n ; j++){
                memo[i][j] = merge(memo[i-1][j], memo[i-1][j + (l >> 1)]) ;
            }
        }

    }

    int get(int l, int r)// get(l, r) expects an inclusive 0-indexed range
    {
        int len = r - l + 1;
        int level = logs[len];
        return merge(memo[level][l], memo[level][r - (1 << level) + 1]);
    }
};

bool isInSubtree(int node, int child ) {
    return tin[node] <= tin[child] && tin[child] < tout[node] ;
}

void solve() {
    int n , m ;cin >> n >> m ;


    vector<vector<pair<int,int>>> adj(n+1);
    for (int i = 1 ; i<= m ;i++) {
        int a ,b , c ;cin >> a >> b >> c ;

        mp[ky(a,b)] = c;
        edges.push_back({a,b,c,i}) ;
    }

    mst(n+1) ;
    dfs(1,-1) ;
    ST st(flat_path) ;
    LCA lca(n, mstAdj, 1);


    vector<int> ans(m+1) ;
    for (auto edj : edges) {
        auto [a,b,c,j] = edj ;

        if (vis[j]) {
            ans[j]=  mstCost ;
            continue;
        }

        if (isInSubtree(b,a)) {
            swap(a,b) ;
        }
        int lc = lca.get(a,b) ;

        ans[j]= mstCost - st.get(tin[lc], tin[a]) - st.get(tin[lc], tin[b]) + flat_path[tin[lc]] + c ;
    }
    for (int timer = tin[3] ; timer <= tin[4] ; timer++)cout << flat_path[timer] << el; 
    // cout << flat_path[tin[4]] ;




    // for (int i=1 ; i<= m ;i++) {
    //     cout << ans[i] <<el ;
    // }

}

void preprocess() {

    // buildfactorial(N) ;
    // buildSPF(N-1) ;
}


signed main()
{

    youssef;
#ifndef ONLINE_JUDGE
    freopen("ts", "r", stdin);
#endif

    int ts = 1;

    preprocess();

    // cin >> ts;
    for (int i = 1; i <= ts; i++)
    {
        // cout << "Case "<< i << ": " ;
        solve();
        // solve2() ;
        cout << el;
    };
}