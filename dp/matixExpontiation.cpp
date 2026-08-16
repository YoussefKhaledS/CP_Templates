#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define youssef ios_base::sync_with_stdio(0); cin.tie(0), cout.tie(0);
#define el '\n'
#define EL '\n'
#define yes "YES"
#define no "NO"
#define ll long long
const ll mod = 1e9 + 7 , infi = 1e17;
int N = 5000002 , loog = 40;
using namespace std;
using namespace __gnu_pbds;
#define int long long
#define Row vector<int>
#define Matrix vector<Row>
/*
 * identitie matrix :
* Example (3x3):
      1 0 0
      0 1 0
      0 0 1
*
*
*For min-plus algebra, the identity matrix is

I[i][i] = 0;
I[i][j] = INF (i != j);

3. Initialization of the transition matrix

You have

Matrix T(n, Row(n,0));

This means

every pair of vertices has an edge of weight 0.

Instead it should be

Matrix T(n, Row(n, INF));

and then fill only the existing edges.
4. matrixminpath() ignores unreachable states

Currently

ret[i][j] = min(ret[i][j], a[i][k] + b[k][j]);

If either operand is INF, you'll compute

INF + something

which is meaningless and may overflow if INF is larger.

You should skip when

a[i][k] == INF || b[k][j] == INF

*
* /



/*
 * A: (n x m), B: (m x p)
 * Requires: A[0].size() == B.size()
 * Returns: A * B (n x p)
 * Time: O(n * m * p)
 */

Matrix matrixMultiply(Matrix &a, Matrix &b) { // O(n^3) but with 1 row o(n^2)
    int n = a.size() ;
    int m = a[0].size() ;
    int p = b[0].size() ;

    Matrix ret(n, vector<int>(p,0)) ;

    for (int i = 0 ; i< n; i++) {
        for (int k = 0 ; k< m ;k++) {
            for (int j = 0 ; j< p ;j++) {
                ret[i][j] += a[i][k] * b[k][j] ;
            }
        }
    }
    return ret ;
}

Matrix identityMatrix(int n) {
    Matrix I(n, vector<int>(n, 0)) ;
    for (int i = 0 ; i< n; i++) {
        I[i][i] = 1 ;
    }
    return I ;
}


/*
 * Requires: matrx is (n x n), p >= 0.
 * Returns: (matrx^p) % MOD.
 * Time: O(n^3 log p)
 */

Matrix matrixPower(Matrix matrx , int p) {
    int n = matrx.size() ;
    Matrix res = identityMatrix(n);

    while (p) {
        if (p&1)
            res = matrixMultiply(res , matrx) ;

        matrx = matrixMultiply(matrx, matrx);
        p>>=1;
    }

    return res ;
}

vector<Matrix> pwT(31) ;
void buildMatrixTPowers() {
    pwT[0] = T ;

    for (int i = 1; i<= 30;i++) {
        pwT[i] = matrixMultiply(pwT[i-1], pwT[i-1]) ;
    }

    int k , n;
    Matrix cur = identityMatrix(n) ;
    for (int b = 0 ; b < 31; b++) {
        if (k & (1ll << b))
            cur = matrixMultiply(cur ,pwT[b]) ;
    }
}







// matrix without using vectors
const int MAX = 55;

struct Matrix {
    int row, col;
    int a[MAX][MAX];

    Matrix() {
        row = col = 0;
        memset(a, 0, sizeof(a));
    }

    Matrix(int r, int c) {
        row = r;
        col = c;
        memset(a, 0, sizeof(a));
    }
};

Matrix matrixMultiply(const Matrix &A, const Matrix &B) {
    Matrix ret(A.row, B.col);

    for (int i = 0; i < A.row; i++) {
        for (int k = 0; k < A.col; k++) {
            for (int j = 0; j < B.col; j++) {
                ret.a[i][j] =
                    (ret.a[i][j] + A.a[i][k] * B.a[k][j]) % mod;
            }
        }
    }

    return ret;
}

Matrix identityMatrix(int n) {
    Matrix I(n, n);

    for (int i = 0; i < n; i++)
        I.a[i][i] = 1;

    return I;
}

Matrix matrixPower(Matrix A, int p) {
    Matrix res = identityMatrix(A.row);

    while (p) {
        if (p & 1)
            res = matrixMultiply(res, A);

        A = matrixMultiply(A, A);
        p >>= 1;
    }

    return res;
}