/*Notes
 *
 */
#include <bits/stdc++.h>
using namespace std;

#define infi 1e6

struct Node {
    long long ans;
    long long lazy;
    bool is_lazy;

    Node() : ans(1e18), lazy(0), is_lazy(0){}
    Node(int x) : ans(x), lazy(0), is_lazy(0){}

    void update(int val, int lx, int rx) {
        ans += val;
        lazy += val;
        is_lazy = 1;
    }
};

struct SegTree {
    int tree_size;
    vector<Node> SegData;
    SegTree(const vector<int> &arr) {
        tree_size = 1;
        int n  = arr.size() ;
        while (tree_size < n) tree_size <<= 1;
        SegData.assign(2 * tree_size, Node());
        build(arr) ;
    }

    Node merge(const Node & lf, const Node & ri) {
        Node ans = Node();
        ans.ans = min(lf.ans, ri.ans);
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
        if(rx - lx == 1)
            return;

        int mid = (lx + rx) / 2;

        if (SegData[node].is_lazy) {
            SegData[2 * node + 1].update(SegData[node].lazy, lx, mid);
            SegData[2 * node + 2].update(SegData[node].lazy, mid, rx);

            SegData[node].lazy = 0;
            SegData[node].is_lazy = 0;
        }
    }

    void set(int l, int r, int val, int node, int lx, int rx) {
        propagate(node, lx, rx);
        if(lx >= r || rx <= l)
            return;
        if(lx >= l && rx <= r) {
            SegData[node].update(val, lx, rx);
            return;
        }

        int mid = (lx + rx) / 2;
        set(l, r, val, 2 * node + 1, lx, mid);
        set(l, r, val, 2 * node + 2, mid, rx);
        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }
    // 0 indexed
    void set(int l, int r, int val) {
        set(l, r, val, 0, 0, tree_size);
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
        return get_range(l, r, 0, 0, tree_size).ans;
    }
};


int main (){


}