#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int sum;
    Node() : sum(0) {};
    Node(int x) : sum(x) {};
};

struct SegTree
{
    int tree_size;
    vector<Node> SegData;

    SegTree(vector<int> &ar)
    {
        tree_size = 1;
        int n = ar.size();
        while (tree_size < n)
            tree_size <<= 1;
        SegData.assign(2 * tree_size, Node());
        build(ar, 0, 0, tree_size);
    }

    Node merge(const Node &lf, const Node &ri)
    {
        Node ans = Node();
        ans.sum = (lf.sum + ri.sum);
        return ans;
    }

    void build(const vector<int> &ar, int node, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < ar.size())
                SegData[node] = Node(ar[lx]);

            return;
        }

        int mid = (lx + rx) / 2;
        build(ar, 2 * node + 1, lx, mid);
        build(ar, 2 * node + 2, mid, rx);

        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }


    void set(int idx, int val, int node, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            SegData[node] = Node(val);
            return;
        }

        int mid = (lx + rx) / 2;
        if (idx < mid)
            set(idx, val, 2 * node + 1, lx, mid);

        else
            set(idx, val, 2 * node + 2, mid, rx);

        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }

    // 0 indexed
    void set(int idx, int val)
    {
        set(idx, val, 0, 0, tree_size);
    }

    void add(int idx, int val, int node, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            SegData[node].sum+=val ;
            return;
        }

        int mid = (lx + rx) / 2;
        if (idx < mid)
            add(idx, val, 2 * node + 1, lx, mid);

        else
            add(idx, val, 2 * node + 2, mid, rx);

        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }

    // 0 indexed
    void add(int idx, int val)
    {
        add(idx, val, 0, 0, tree_size);
    }

    Node get_range(int l, int r, int node, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return Node();

        if (lx >= l && rx <= r)
            return SegData[node];

        int mid = (lx + rx) / 2;
        Node lf = get_range(l, r, 2 * node + 1, lx, mid);
        Node ri = get_range(l, r, 2 * node + 2, mid, rx);

        return merge(lf, ri);
    }
    // r is execlusive
    int get_range(int l, int r)
    {
        return get_range(l, r, 0, 0, tree_size).sum;
    }

    int find_first(int l, int r, int val, int node, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return -1;

        if (SegData[node].sum < val)
            return -1;

        if (rx - lx == 1)
            return lx;

        int mid = (lx + rx) / 2;
        int ans = find_first(l, r, val, 2 * node + 1, lx, mid);

        if (ans == -1)
            ans = find_first(l, r, val, 2 * node + 2, mid, rx);

        return ans;
    }

    int find_first(int l, int r, int val)
    {
        return find_first(l, r, val, 0, 0, tree_size);
    }

    int kth(int cnt, int node, int lx, int rx)
    {
        if (rx - lx == 1)
            return lx;

        int mid = (lx + rx) / 2;
        int lf_sum = SegData[2 * node + 1].sum;
        if (lf_sum >= cnt)
            return kth(cnt, 2 * node + 1, lx, mid);
        else
            return kth(cnt - lf_sum, 2 * node + 2, mid, rx);
    }
    int kth(int cnt)
    {
        return kth(cnt, 0, 0, tree_size);
    }
};



struct SegTree2//lazy probagation
{
    int tree_size;
    vector<Node> SegData;
    vector<int> lazy;
    vector<bool> has_lazy;

    SegTree2(vector<int> &ar)
    {
        tree_size = 1;
        int n = ar.size();
        while (tree_size < n)
            tree_size <<= 1;

        SegData.assign(2 * tree_size, Node());
        lazy.assign(2 * tree_size, 0);
        has_lazy.assign(2 * tree_size, false);

        build(ar, 0, 0, tree_size);
    }

    Node merge(const Node &lf, const Node &ri)
    {
        return Node(lf.sum + ri.sum);
    }

    void build(const vector<int> &ar, int node, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < (int)ar.size())
                SegData[node] = Node(ar[lx]);
            return;
        }

        int mid = (lx + rx) / 2;
        build(ar, 2 * node + 1, lx, mid);
        build(ar, 2 * node + 2, mid, rx);

        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }

    // 🔥 apply lazy value
    void apply(int node, int lx, int rx, int val)
    {
        SegData[node].sum = (rx - lx) * val;
        lazy[node] = val;
        has_lazy[node] = true;
    }

    // 🔥 push to children
    void push(int node, int lx, int rx)
    {
        if (!has_lazy[node] || rx - lx == 1)
            return;

        int mid = (lx + rx) / 2;

        apply(2 * node + 1, lx, mid, lazy[node]);
        apply(2 * node + 2, mid, rx, lazy[node]);

        has_lazy[node] = false;
    }

    // 🔹 point set
    void set(int idx, int val, int node, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            SegData[node] = Node(val);
            return;
        }

        push(node, lx, rx);

        int mid = (lx + rx) / 2;
        if (idx < mid)
            set(idx, val, 2 * node + 1, lx, mid);
        else
            set(idx, val, 2 * node + 2, mid, rx);

        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }

    void set(int idx, int val)
    {
        set(idx, val, 0, 0, tree_size);
    }

    // 🔹 point add
    void add(int idx, int val, int node, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            SegData[node].sum += val;
            return;
        }

        push(node, lx, rx);

        int mid = (lx + rx) / 2;
        if (idx < mid)
            add(idx, val, 2 * node + 1, lx, mid);
        else
            add(idx, val, 2 * node + 2, mid, rx);

        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }

    void add(int idx, int val)
    {
        add(idx, val, 0, 0, tree_size);
    }

    // 🔥 range set
    void set_range(int l, int r, int val, int node, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return;

        if (lx >= l && rx <= r)
        {
            apply(node, lx, rx, val);
            return;
        }

        push(node, lx, rx);

        int mid = (lx + rx) / 2;
        set_range(l, r, val, 2 * node + 1, lx, mid);
        set_range(l, r, val, 2 * node + 2, mid, rx);

        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }

    void set_range(int l, int r, int val)
    {
        set_range(l, r, val, 0, 0, tree_size);
    }

    // 🔹 range query
    Node get_range(int l, int r, int node, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return Node();

        if (lx >= l && rx <= r)
            return SegData[node];

        push(node, lx, rx);

        int mid = (lx + rx) / 2;
        Node lf = get_range(l, r, 2 * node + 1, lx, mid);
        Node ri = get_range(l, r, 2 * node + 2, mid, rx);

        return merge(lf, ri);
    }

    int get_range(int l, int r)
    {
        return get_range(l, r, 0, 0, tree_size).sum;
    }

    // 🔹 find first index with prefix sum ≥ val
    int find_first(int l, int r, int val, int node, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return -1;

        if (SegData[node].sum < val)
            return -1;

        if (rx - lx == 1)
            return lx;

        push(node, lx, rx);

        int mid = (lx + rx) / 2;
        int ans = find_first(l, r, val, 2 * node + 1, lx, mid);
        if (ans == -1)
            ans = find_first(l, r, val, 2 * node + 2, mid, rx);

        return ans;
    }

    int find_first(int l, int r, int val)
    {
        return find_first(l, r, val, 0, 0, tree_size);
    }

    // 🔹 kth element (by frequency / prefix sum)
    int kth(int cnt, int node, int lx, int rx)
    {
        if (rx - lx == 1)
            return lx;

        push(node, lx, rx);

        int mid = (lx + rx) / 2;
        int lf_sum = SegData[2 * node + 1].sum;

        if (lf_sum >= cnt)
            return kth(cnt, 2 * node + 1, lx, mid);
        else
            return kth(cnt - lf_sum, 2 * node + 2, mid, rx);
    }

    int kth(int cnt)
    {
        return kth(cnt, 0, 0, tree_size);
    }
};