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
const ll mod = 998244353 , infi = 1e18;
int N = 5000002 , loog = 40;
using namespace std;
#define int long long

void fun1() {// convert char to string
    to_string(1,'a') ;
}

void fun2() { // create array vector with numbers from 1 to n
    // vector<int> = {1, 2, 3, ..., n}
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
}

void func3() {// convert string transform string
    int x = stoll("235234324") ;

}
int sumOfSequenceStartingFromKtoN(int k, int n) {// sum of sequence starting from k to n 
    return n * (2 * k + n - 1) / 2;
}
// to delete element from vector by its value v.erase(remove(v.begin(), v.end(), value), v.end());

// to sort vector by second element
/*
sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
    return a.second < b.second;
});
 */

// vector<array<int,3>> ar;
// cin into ar[i]:
//   cin >> ar[i][0] >> ar[i][1] >> ar[i][2];
//   or: for(auto &x : ar[i]) cin >> x;
// sort: default is lex (by [0], then [1], then [2])
//   sort(ar.begin(), ar.end());
// sort by one index (e.g. [1]):
/*
sort(ar.begin(), ar.end(), [](const auto &a, const auto &b) {
    return a[1] < b[1];
});
*/
// multi-key (e.g. [0] asc, then [1] desc):
/*
sort(ar.begin(), ar.end(), [](const auto &a, const auto &b) {
    if (a[0] != b[0]) return a[0] < b[0];
    return a[1] > b[1];
});
*/
// lower_bound (must sort first with same order)
// full key:
//   auto it = lower_bound(ar.begin(), ar.end(), array<int,3>{x, y, z});
// by first only (sorted by [0]):
/*
auto it = lower_bound(ar.begin(), ar.end(), x, [](const auto &a, int val) {
    return a[0] < val;
});
*/
// index: it - ar.begin()  |  not found / past end: it == ar.end()
