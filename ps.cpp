#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define youssef ios_base::sync_with_stdio(0); cin.tie(0), cout.tie(0);
#define el '\n'
#define EL '\n'
#define yes "YES"
#define no "NO"
#define ll long long
const ll mod = 998244353 , infi = LONG_MAX;
int N = 5e5 , loog = 30;
using namespace std;
#define int long long

int dx[] = {-1, 0 , 1 ,0};
int dy[] = {0, 1 , 0 ,-1};
int n , m ;
void dfsgrid(int x, int y, vector<vector<char>> &grid , vector<vector<bool>> &vis) {

    vis[x][y] = 1;

    for (int i = 0 ; i< 4 ;i++) {
        int nx = x +dx[i] ;
        int ny = y+ dy[i] ;

        if (nx < 0 || ny < 0 || nx >= n || ny >= m)continue;
        if (vis[nx][ny] || grid[nx][ny] == '#' || grid[nx][ny] == 'X')continue;

        dfsgrid(nx, ny, grid, vis) ;
    }
}


void solve()
{
    int k ;cin >> n >> m >> k ;
    vector<vector<char>> grid(n, vector<char>(m)) ;
    int s = 0 , stx , sty ;

    for (int i = 0 ; i< n; i++) {
        for (int j = 0 ; j< m; j++) {
            cin >> grid[i][j] ;
            if (grid[i][j] == '.') {
                s++;
                stx = i ;
                sty = j ;
            }
        }
    }
    int free = s - k-1;
    vector<vector<bool>> vis(n, vector<bool>(m, false)) ;
    dfsgrid(stx,sty, free, grid, vis);

    for (int i = 0 ; i< n; i++) {
        for (int j = 0 ; j< m; j++) {
            cout << grid[i][j] ;
        }cout << el;
    }


}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("ts", "r", stdin);
#endif
    youssef;
    int ts = 1;

    // cin >> ts;
    for (int i = 1; i <= ts; i++)
    {
        solve();
        // cout << el;
    }
}


