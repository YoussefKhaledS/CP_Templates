#include <bits/stdc++.h>
using namespace std; 

struct ST{
    vector<vector<int>> memo ;
    vector<int> logs;

    int merge(int &lf, int &ri)
    {
        return min(lf, ri);
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

    int get(int l, int r)
    {
        int len = r - l + 1;
        int level = logs[len];
        return merge(memo[level][l], memo[level][r - (1 << level) + 1]);
    }
};
