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

/*
 * identitie matrix :
* Example (3x3):
      1 0 0
      0 1 0
      0 0 1
*
* /



/*
 * A: (n x m), B: (m x p)
 * Requires: A[0].size() == B.size()
 * Returns: A * B (n x p)
 * Time: O(n * m * p)
 */

vector<vector<int>> matrixMultiply(vector<vector<int>> &a, vector<vector<int>> &b) {
    int n = a.size() ;
    int m = a[0].size() ;
    int p = b[0].size() ;

    vector<vector<int>> ret(n, vector<int>(p,0)) ;

    for (int i = 0 ; i< n; i++) {
        for (int k = 0 ; k< m ;k++) {
            for (int j = 0 ; j< p ;j++) {
                ret[i][j] += a[i][k] * b[k][j] ;
            }
        }
    }
}

vector<vector<int>> identityMatrix(int n) {
    vector<vector<int>> I(n, vector<int>(n, 0)) ;
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

vector<vector<int>> matrixPower(vector<vector<int>> matrx , int p) {
    int n = matrx.size() ;
    vector<vector<int>> res = identityMatrix(n);

    while (p) {
        if (p&1)
            res = matrixMultiply(res , matrx) ;

        matrx = matrixMultiply(matrx, matrx);
        p>>=1;
    }

    return res ;
}