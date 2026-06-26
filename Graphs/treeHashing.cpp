// Tree Hashing (Subtree Hashing) for a rooted tree
// In case tree is unrooted, you must use "isophrisim.cpp"
// Time Complexity: O(n log n)
//Without sorting: O(n) (plus map lookups).
//With sorting: O(nlogn) in the worst case.

// This function computes a hash for each subtree in a rooted tree.
// It can be used to test subtree isomorphism. Optionally, sort children
// before hashing to ignore child order (unordered rooted tree).


#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define youssef ios_base::sync_with_stdio(0); cin.tie(0), cout.tie(0);
#define el '\n'
#define EL '\n'
#define yes "Yes"
#define no "No"
#define ll long long
const ll mod = 1e9+7 , infi = 1e17;
int N = 1e5 + 4 , loog = 40;
using namespace std;
#define int long long


map<vector<int>, int> mp ;

void tree_hash(int u,int p, vector<int> &hash, vector<vector<int>> &adj) {
    vector<int> childeren ;

    for (auto &v: adj[u]) {
        if (v != p) {
            tree_hash(v, u, hash, adj) ;
            childeren.emplace_back(hash[v]) ;
        }
    }

    // if the order of childerenren does not matter
    // sort(childeren.begin(), childeren.end() );

    // insert yourself in the childeren array to hash the full subtree
    if (!mp.count(childeren)) {
        mp[childeren] = mp.size() +1 ;
    }
    hash[u] = mp[childeren] ;
}
