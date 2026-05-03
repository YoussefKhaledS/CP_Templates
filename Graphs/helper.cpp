


// dfs on n*m grid
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
