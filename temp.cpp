#include <iostream>
#include <bits/stdc++.h>
#define youssef                   \
    ios_base::sync_with_stdio(0); \
    cin.tie(0), cout.tie(0);
#define el '\n'
#define EL '\n'
#define ll long long
#define yes "YES"
#define no "NO"
// #define int long long
const ll mod = 1e9 + 7, infi = LONG_MAX;
int N = 1e6+8;
using namespace std;
#define int long long

struct LCA
{
    int **memo, log;
    vector<int> *adjlist, lev;

    LCA(int n, vector<int> *_adjlist, int root)
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

        for (int v : adjlist[u])
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

LCA* lca ;

int modsum(int a, int b){
    return (a%mod + b%mod)%mod; 
}
int modmult(int a, int b){
    return (a%mod * b%mod)%mod ;
}

vector<vector<int>> dpdown  ;
vector<int> dpup ;
int dfs1(int node, bool bad, int parent, vector<int> *adjlist){

    int &ret = dpdown[node][bad] ;
    if(ret != -1)return ret ;
    ret = 1; 

    for(auto child : adjlist[node]){
        
        if(child != parent){
            int t = dfs1(child, bad, node, adjlist) ;
            if(!bad)t = modsum(t, dfs1(child, 1, node, adjlist)) ;
            
            if(t)ret = modmult(t,ret);
        }
    }

    return ret ;
}

void dfs2(int node, int parent, vector<int> *adjlist){
    
    if(node != 1){
        int res = 1 ;
        int gparent = lca->kth(parent, 1) ;
        for(auto bro: adjlist[parent]){

            if(bro != node && bro != gparent){
                int brovalue = modsum(dpdown[bro][0], dpdown[bro][1]);
                res = modmult(res, brovalue) ;
            }
            
        }
        if(parent != 1)
            res = modmult(res, dpup[parent]) ;
        dpup[node] = res; 
    }



    for(auto child : adjlist[node]){
        if(parent != child){
            dfs2(child , node, adjlist) ;
        }
    }
}
void solve()
{
    int n;cin >> n ;
    vector<int> adjlist[n+1] , depth(n+1 , 0) ;
    for(int i = 2 ; i<= n ;i++){
        int x ;cin >> x ;
        adjlist[i].push_back(x) ;
        adjlist[x].push_back(i) ;
    } 
    lca = new LCA(n ,adjlist , 1) ;
    dpdown.assign(n+1 , vector<int>(2, -1)) ;
    dpup.assign(n+1, 0) ;
    cout << dfs1(1, 0 , -1, adjlist) <<" ";
    dfs2(1,1,adjlist); 
    
    for(int i =2 ; i<= n; i++){
        int ans = dpup[i];
        // cout << ans << ' ' ; 
        int parent = lca->kth(i, 1) ;
        for(auto child : adjlist[i]){
            if(child != parent){
                int temp = modsum(dpdown[child][1] , dpdown[child][0]) ;
                ans = modmult(ans, max(temp,(int)1) ) ;
            }
        }

        cout << ans << ' ' ;
    }
}

signed main()
{
    youssef;
    int ts = 1;
    

    // cin >> ts;
    for(int i = 1 ; i<= ts ; i++)
    {
        solve();
        // cout << el;
    }
}