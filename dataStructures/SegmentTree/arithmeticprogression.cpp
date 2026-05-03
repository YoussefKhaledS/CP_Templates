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

/*
 * add arithmetic progression on range and get range
 *
 * a+ a+d + a+2d + a+3d etc.....
 */

struct Node {
    long long sum = 0;
    long long a = 0, d = 0;
    bool is_lazy = 0;

    Node() {}
    Node(int x) : sum(x){}

    void update(int new_a, int new_d, int lx, int rx) {
        int L = rx - lx;
        sum += new_a * L + new_d * L * (L - 1) / 2;
        a += new_a;
        d += new_d;
        is_lazy = 1;
    }
};

struct SegTree {
    int tree_size;
    vector<Node> SegData;
    SegTree(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size <<= 1;
        SegData.assign(2 * tree_size, Node());
    }

    Node merge(const Node & lf, const Node & ri) {
        Node ans = Node();
        ans.sum = lf.sum + ri.sum;
        return ans;
    }

    void build(const vector<int> & arr, int node, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < arr.size())
                SegData[node] = Node(arr[lx]);
            return;
        }

        int mid = (lx + rx) / 2;
        build(arr, 2 * node + 1, lx, mid);
        build(arr, 2 * node + 2, mid, rx);

        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }
    void build(const vector<int> & arr) {
        build(arr, 0, 0, tree_size);
    }

    void propagate(int node, int lx, int rx) {
        if(rx - lx == 1 || SegData[node].is_lazy == 0)
            return;

        int mid = (lx + rx) / 2;

        SegData[2 * node + 1].update(SegData[node].a, SegData[node].d, lx, mid);
        SegData[2 * node + 2].update(
                SegData[node].a + SegData[node].d * (rx - lx) / 2,
                SegData[node].d, mid, rx);

        SegData[node].a = SegData[node].d = 0;
        SegData[node].is_lazy = 0;
    }

    void set(int l, int r, int a, int d, int node, int lx, int rx) {
        propagate(node, lx, rx);
        if(lx >= r || rx <= l)
            return;
        if(lx >= l && rx <= r) {
            SegData[node].update(a + (lx - l) * d, d, lx, rx);
            return;
        }

        int mid = (lx + rx) / 2;
        set(l, r, a, d, 2 * node + 1, lx, mid);
        set(l, r, a, d, 2 * node + 2, mid, rx);
        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }
    // 0 indexed
    void set(int l, int r, int a, int d) {
        set(l, r, a, d, 0, 0, tree_size);
    }

    Node get_range(int l, int r, int node, int lx, int rx) {
        propagate(node, lx, rx);
        if(lx >= r || rx <= l)
            return Node();
        if(lx >= l && rx <= r)
            return SegData[node];

        int mid = (lx + rx) / 2;
        Node lf = get_range(l, r, 2 * node + 1, lx, mid);
        Node ri = get_range(l, r, 2 * node + 2, mid, rx);

        return merge(lf, ri);
    }

    // r is not inclusive [l, r)
    long long get_range(int l, int r) {
        return get_range(l, r, 0, 0, tree_size).sum;
    }
};
