#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define youssef ios_base::sync_with_stdio(0); cin.tie(0), cout.tie(0);
#define el '\n'
#define EL '\n'
#define yes "Yes"
#define no "No"
#define ll long long
const ll mod = 1e9 + 7 , infi = 1e17;
int N = 1e8+3, loog = 40;
using namespace std;
using namespace __gnu_pbds;
#define int long long
// #define int uint64_t
// #define u128 __uint128_t
// todo convert dfs->bfs easly

vector<bool> vis;

void dfs(int node, vector<vector<pair<int,int>>> &adj, vector<int> &res) {// this for step1 and filling each scc component
    vis[node] = 1 ;

    for (auto [child, w] : adj[node]) {
        if (vis[child])continue;
        dfs(child , adj, res);
    }

    res.push_back(node);
}

vector<vector<int>> components ;
vector<vector<pair<int,int>>> sccAdj;
vector<int> sccRoots, components_sccRoots, sccRoots_components;

void scc(vector<vector<pair<int,int>>> &adj) {

    int n = adj.size();
    vector<int> order; // finishing order

    vis.assign(n, 0);

    // step 1: dfs to find finishing order
    for (int i = 1 ; i< n; i++) {
        if (!vis[i])
            dfs(i, adj, order) ;
    }

    // step2: reverse the graph
    vector<vector<pair<int,int>>> revAdj(n) ;
    for (int node = 1 ; node < n; node++) {
        for (auto [child, w] : adj[node]) {
            revAdj[child].push_back({node,w});
        }
    }

    vis.assign(n, 0) ;
    reverse(order.begin(),order.end());

    sccRoots.assign(n, 0) ;// to store the scc root for each node
    components_sccRoots.assign(n, -1) ;// to store the component id for each scc root
    sccRoots_components.assign(n, -1) ;

    // step 3: last dfs to create the scc
    for (int v : order) {
        if (vis[v])continue;

        vector<int> component ;
        dfs(v, revAdj, component);

        components.push_back(component);

        int root = component.front() ;
        components_sccRoots[components.size()-1] =  root;
        sccRoots_components[root] = components.size()-1;

        for (int u : component)
            sccRoots[u] = root ;
    }

    // create the new decomposed scc graph
    sccAdj.assign(n, {});
    for (int v = 1 ; v < n; v++) {
        for (auto [u,w] : adj[v]) {
            if (sccRoots[v] != sccRoots[u]) {
                sccAdj[sccRoots[v]].push_back({sccRoots[u],w});
            }
        }
    }
}

int findy(int x ) {
    int start = 0 , end = x ;
    int ans = 0;
    while (start <= end) {
        int mid = (start + end)/2 ;
        int y = mid*(mid+1) /2 ;
        if (y < x) {
            ans = mid ;
            start = mid+1;
        }else {
            end = mid-1;
        }
    }
    return ans ;
}

ll calc(int x , int y) {
    ll a = (y*(y+1))/2 ;
    ll b = (y*(y+1)*(2*y+1))/6 ;

    return x*(y+1) - ((a+b)/2);
}

void solve() {

    int n , m;cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n+1) ;

    while (m--) {
        int a , b , w;cin >> a >> b >> w  ;
        adj[a].push_back({b,w});
    }

    scc(adj) ;

    m = components.size() ;
    vector<ll> sums(m ), dp(m ,  0);

    for (int i = 0 ; i< m ;i++) {
        ll sum = 0 ;

        for (auto node : components[i]) {
            for (auto [child, w]: adj[node]) {

                if (sccRoots[node] != sccRoots[child])continue;

                int y = findy(w);
                // int y = gety[w];
                sum+=calc(w,y) ;
            }
        }
        sums[i] = sum ;
        // cout << sum << ' ' ;
    }


    dp[m-1] = sums[m-1] ;

    for (int i = m -2 ; i>= 0 ;i--) {
        int root = components_sccRoots[i] ;
        dp[i] =sums[i] ;

        for (auto [child,w] : sccAdj[root]) {
            dp[i] = max(dp[i] , dp[sccRoots_components[child]] + sums[i] + w) ;
        }
    }
    int s;cin >> s;
    cout << dp[sccRoots_components[sccRoots[s]]] ;

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