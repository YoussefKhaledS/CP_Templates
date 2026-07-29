struct ST2D {
    vector<vector<vector<vector<int>>>> memo;
    vector<int> logs;

    int merge(int &a, int &b) {
        return min(a, b);
    }

    ST2D(vector<vector<int>> &grid) {
        int n = grid.size();
        int m = grid[0].size();

        int mx = max(n, m);
        logs.assign(mx + 1, 0);

        for (int i = 2; i <= mx; i++)
            logs[i] = logs[i / 2] + 1;

        memo.assign(logs[n] + 1,
                    vector<vector<vector<int>>>(
                        logs[m] + 1));

        // 2^0 x 2^0
        memo[0][0] = grid;

        // Build horizontally
        for (int j = 1; j <= logs[m]; j++) {
            int len = 1 << j;
            memo[0][j].assign(n, vector<int>(m - len + 1));

            for (int i = 0; i < n; i++) {
                for (int k = 0; k + len <= m; k++) {
                    memo[0][j][i][k] =
                        merge(memo[0][j - 1][i][k],
                              memo[0][j - 1][i][k + (len >> 1)]);
                }
            }
        }

        // Build vertically
        for (int i = 1; i <= logs[n]; i++) {
            int len = 1 << i;

            for (int j = 0; j <= logs[m]; j++) {
                int len2 = 1 << j;

                memo[i][j].assign(n - len + 1,
                                  vector<int>(m - len2 + 1));

                for (int x = 0; x + len <= n; x++) {
                    for (int y = 0; y + len2 <= m; y++) {
                        memo[i][j][x][y] =
                            merge(memo[i - 1][j][x][y],
                                  memo[i - 1][j][x + (len >> 1)][y]);
                    }
                }
            }
        }
    }

    int get(int x1, int y1, int x2, int y2) {
        int kx = logs[x2 - x1 + 1];
        int ky = logs[y2 - y1 + 1];

        int nx = x2 - (1 << kx) + 1;
        int ny = y2 - (1 << ky) + 1;

        int a = merge(memo[kx][ky][x1][y1],
                      memo[kx][ky][nx][y1]);

        int b = merge(memo[kx][ky][x1][ny],
                      memo[kx][ky][nx][ny]);

        return merge(a, b);
    }
};


/*
    2D Sparse Table (Idempotent Rectangle Queries)

    Complexity:
    - Build : O(n * m * log n * log m)
    - Query : O(1)
    - Memory: O(n * m * log n * log m)

    Supports ONLY idempotent associative operations:
    - min
    - max
    - gcd
    - bitwise AND
    - bitwise OR

    NOT suitable for:
    - sum
    - xor
    - product
    - any non-idempotent operation

    Idea:
    memo[kx][ky][i][j] stores the answer for rectangle:
        rows    [i, i + 2^kx - 1]
        columns [j, j + 2^ky - 1]

    Build:
    1) Build horizontally (ky):
        Merge two adjacent rectangles of width 2^(ky-1).

    2) Build vertically (kx):
        Merge two adjacent rectangles of height 2^(kx-1).

    Query rectangle:
        (x1,y1) -> (x2,y2)

        kx = floor(log2(height))
        ky = floor(log2(width))

        Take the four largest overlapping rectangles:

            A = memo[kx][ky][x1][y1]
            B = memo[kx][ky][x2-2^kx+1][y1]
            C = memo[kx][ky][x1][y2-2^ky+1]
            D = memo[kx][ky][x2-2^kx+1][y2-2^ky+1]

        Answer = merge(merge(A,B), merge(C,D))

    Visualization:

        +-----------------------+
        | A             | C     |
        |               |       |
        |---------------+-------|
        | B             | D     |
        +-----------------------+

    Why only idempotent?
    The four rectangles overlap.
    Elements in the intersections may be merged multiple times,
    so merge(x,x) must equal x.

    Common Uses:
    - 2D Range Minimum Query
    - 2D Range Maximum Query
    - Static grid queries
    - Image/terrain rectangle queries

    Note:
    Memory is huge:
        O(n * m * log n * log m)

    Practical only for relatively small grids
    (typically <= 500~1000 per dimension depending on memory limit).
    For large grids (e.g. n,m=3000), prefer MonoQueue/Deque
    sliding-window techniques when applicable.
*/