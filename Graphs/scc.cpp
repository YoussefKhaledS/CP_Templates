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


// Kosaraju's Algorithm

/*
    Step 1: DFS and finishing order
    Step 2: Reverse the graph
    Step 3: Process nodes in reverse finishing order
        Each DFS gives us one complete SCC.
*/

vector<bool> vis;

void dfs(int node, vector<vector<int>> &adj, vector<int> &res) {// this for step1 and filling each scc component
    vis[node] = 1 ;

    for (auto child : adj[node]) {
        if (vis[child])continue;
        dfs(child , adj, res);
    }

    res.push_back(node);
}

vector<vector<int>> components , sccAdj;
vector<int> sccRoots, sccRoots_components;
void scc(vector<vector<int>> &adj) {

    int n = adj.size();
    vector<int> order; // finishing order

    vis.assign(n, 0);

    // step 1: dfs to find finishing order
    for (int i = 0 ; i< n; i++) {
        if (!vis[i])
            dfs(i, adj, order) ;
    }

    // step2: reverse the graph
    vector<vector<int>> revAdj(n) ;
    for (int node = 0 ; node < n; node++) {
        for (int child : adj[node]) {
            revAdj[child].push_back(node);
        }
    }

    vis.assign(n, 0) ;
    reverse(order.begin(),order.end());

    sccRoots.assign(n, 0) ;// to store the scc root for each node
    sccRoots_components.assign(n, -1) ;// to store the component id for each scc root

    // step 3: last dfs to create the scc
    for (int v : order) {
        if (vis[v])continue;

        vector<int> component ;
        dfs(v, revAdj, component);

        components.push_back(component);

        int root = component.front() ;
        sccRoots_components[root] = components.size() -1;
        for (int u : component)
            sccRoots[u] = root ;
    }

    // create the new decomposed scc graph
    sccAdj.assign(n, {});
    for (int v = 0 ; v < n; v++) {
        for (int u : adj[v]) {
            if (sccRoots[v] != sccRoots[u]) {
                sccAdj[sccRoots[v]].push_back(sccRoots[u]);
            }
        }
    }
}






// strongly connected component -> self-contaned cycles in a directed graph

// low-link value -> smallest node id reachable from current node lowlink[node] = smallest node id reachable from node


vector<int> st;    // - stack holding the unclaimed vertices
vector<int> roots; // - keeps track of the SCC roots of the vertices
int timer;         // - dfs timestamp counter
vector<int> t_in;  // - keeps track of the dfs timestamp of the vertices
vector<int> t_low; // - keeps track of the lowest t_in of unclaimed vertices
                   // reachable in the subtree

// implements the tarjan algorithm for strongly connected components
void dfs(int v, vector<vector<int>> const &adj, vector<vector<int>> &components) {

  t_low[v] = t_in[v] = timer++;
  st.push_back(v);

  for (auto u : adj[v]) {
    if (t_in[u] == -1) { // tree-edge
      dfs(u, adj, components);
      t_low[v] = min(t_low[v], t_low[u]);
    } else if (roots[u] == -1) { // back-edge, cross-edge or forward-edge to an unclaimed vertex
      t_low[v] = min(t_low[v], t_in[u]);
    }
  }

  if (t_low[v] == t_in[v]) { // vertex is a root
    components.push_back({v}); // initializes a new component with root v
    while (true) {
      int u = st.back();
      st.pop_back();
      roots[u] = v; // claims the vertex
      if (u == v)
        break;
      components.back().push_back(u); // adds vertex u to the component of v
    }
  }
}

// input: adj -- adjacency list of G
// output: components -- the strongy connected components in G
// output: adj_cond -- adjacency list of G^SCC (by root vertices)
void strongly_connected_components(vector<vector<int>> const &adj,
                                   vector<vector<int>> &components,
                                   vector<vector<int>> &adj_cond) {
  components.clear();
  adj_cond.clear();

  int n = adj.size();

  st.clear();
  roots.assign(n, -1);
  timer = 0;
  t_in.assign(n, -1);
  t_low.assign(n, -1);

  // applies the tarjan algorithm to all the vertices
  // adds vertices to the components in reverse topological order
  for (int v = 0; v < n; v++) {
    if (t_in[v] == -1) {
      dfs(v, adj, components);
    }
  }

  // adds edges to the condensation graph
  adj_cond.assign(n, {});
  for (int v = 0; v < n; v++) {
    for (auto u : adj[v])
      if (roots[v] != roots[u])
        adj_cond[roots[v]].push_back(roots[u]);
  }
}