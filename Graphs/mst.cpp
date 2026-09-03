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


/*
Time: O(M log N)
Memory: O(N + M)
 works on Weighted undirected graphs

The graph should be connected
    If the graph is connected, Prim produces one MST containing all N vertices.
    If the graph is disconnected, Prim starting from one node only visits its connected component. (you can make MS Forest)

the result is connected TREE with minimum sum of edges

The MST is not always unique
If all edge weights are distinct, the MST is unique

Negative * zero weights are completely fine

multiple and self loops are allowd

Kruskal with Disjoint Set Union steps

1- sort edges by ascending edge weight
2- 

*/

