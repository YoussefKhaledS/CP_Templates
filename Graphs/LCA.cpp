#include <bits/stdc++.h>
using namespace std;

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


int main(){

}