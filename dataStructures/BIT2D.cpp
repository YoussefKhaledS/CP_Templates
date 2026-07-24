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
const ll mod = 1e9 + 7 , infi = 1e17;
int N = 5000002 , loog = 40;
using namespace std;
#define int long long
/*
 *template expect 0-indexed coordnate
 *rows need compression if too large
 *
 *What does  it solve  ?
 *  point update with rectangle sum queries
 *  when you have 2 constrains to calculate something
 *  range queries with constrains on the values in the range
 *
 *constructor attributes:
 * n is the maximum row index.
 * todo contains every point that may be ever added or updated.
 *
 *Time complexity
 *  preprocessing -> O(Q logN)
 *  update -> O(log^2)
 *  query -> O(log^2)
 *
 *  memory -> O(Q logN)
 *
 *  usages->
        *  vector<array<int,2>> updates;

        // Collect every point that will ever be updated
        updates.push_back({1,3});
        updates.push_back({2,5});
        updates.push_back({4,7});

        // Build
        OfflineBIT2D<long long> bit(5, updates);

        // Perform updates
        bit.add(1,3,10);
        bit.add(2,5,20);
        bit.add(4,7,30);

        // Prefix query
        cout << bit.rect_sum(2,5) << "\n";   // 30

        // Rectangle query
        cout << bit.rect_sum(1,3,4,7) << "\n"; // 60
 */

template <typename T> class OfflineBIT2D {
private:
    const int n;
    vector<vector<int>> vals;
    vector<vector<T>> bit;

    /** @return the first index i such that v[i] <= x */
    int ind(const vector<int> &v, int x) {
        return upper_bound(begin(v), end(v), x) - begin(v) - 1;
    }

public:
    OfflineBIT2D(int n, vector<array<int, 2>> &todo) : n(n), vals(n + 1), bit(n + 1) {
        sort(begin(todo), end(todo),
             [](const array<int, 2> &a, const array<int, 2> &b) -> bool {
                 return a[1] < b[1];
             });

        for (int i = 1; i <= n; i++) { vals[i].push_back(0); }
        for (auto [r, c] : todo) {
            r++, c++;
            for (; r <= n; r += r & -r) {
                if (vals[r].back() != c) { vals[r].push_back(c); }
            }
        }
        for (int i = 1; i <= n; i++) { bit[i].resize(vals[i].size()); }
    }

    /** adds val to the point (r, c) */
    void add(int r, int c, T val) {
        r++, c++;
        for (; r <= n; r += r & -r) {
            int i = ind(vals[r], c);
            for (; i < bit[r].size(); i += i & -i) { bit[r][i] += val; }
        }
    }

    /** @returns sum of points with row in [0, r] and column in [0, c] */
    T rect_sum(int r, int c) {
        r++, c++;
        T sum = 0;
        for (; r > 0; r -= r & -r) {
            int i = ind(vals[r], c);
            for (; i > 0; i -= i & -i) { sum += bit[r][i]; }
        }
        return sum;
    }

    /** @returns sum of points with row in [r1, r2] and column in [c1, c2]
     */
    T rect_sum(int r1, int c1, int r2, int c2) {
        return rect_sum(r2, c2) - rect_sum(r2, c1 - 1) - rect_sum(r1 - 1, c2) +
               rect_sum(r1 - 1, c1 - 1);
    }

    /** @returns  the value stored at point (r,c) **/
    T get(int r, int c) {
        return rect_sum(r, c, r, c);
    }

};