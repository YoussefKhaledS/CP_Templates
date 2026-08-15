
#include <bits/stdc++.h>
using namespace std;

#define infi 1e6
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





int main (){
    vector<int> ar = {3,5,1,3,6,6,1,61,6,82,552,31,11,5,6,7,1,9} ;

    SegTree segtree(ar);

    cout <<  segtree.sumgreater(0,6 , 0) ;

}