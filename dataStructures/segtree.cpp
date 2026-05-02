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


// merge segtree
struct Node
{
    vector<int> ar, pref;
    int mx, mn;
    Node()
    {
        ar = {};
        pref = {} ;
        mx = 0;
        mn = infi;
    }
    Node(vector<int> _ar)
    {
        ar = _ar;
        pref= _ar;
        mx = _ar[0];
        mn = _ar[0];
    }
};

struct SegTree
{
    int tree_size;
    vector<Node> SegData;
    SegTree(vector<int> &arr)
    {
        tree_size = 1;
        int n = arr.size();
        while (tree_size < n)
            tree_size <<= 1;
        SegData.assign(2 * tree_size, {});
        build(arr);
    }

    Node merge(const Node &lf, const Node &ri)
    {
        int n = lf.ar.size(), m = ri.ar.size();
        Node ans = Node();
        ans.ar.resize(n + m);
        ans.pref.resize(n + m);

        int i = 0, j = 0, k = 0;
        while (i < n && j < m)
        {
            if (lf.ar[i] < ri.ar[j])
                ans.ar[k++] = lf.ar[i++];
            else
                ans.ar[k++] = ri.ar[j++];
        }

        while (i < n)
            ans.ar[k++] = lf.ar[i++];
        while (j < m)
            ans.ar[k++] = ri.ar[j++];

        for(int i = 0 ; i< n+m ; i++){
            ans.pref[i] = (i != 0)? ans.pref[i-1] + ans.ar[i] : ans.ar[i] ;
        }

        ans.mx = max(lf.mx, ri.mx);
        ans.mn = min(lf.mn, ri.mn);
        return ans;
    }

    void build(const vector<int> &arr, int node, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < arr.size())
                SegData[node] = Node({arr[lx]});
            return;
        }

        int mid = (lx + rx) / 2;
        build(arr, 2 * node + 1, lx, mid);
        build(arr, 2 * node + 2, mid, rx);

        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }
    void build(const vector<int> &arr)
    {
        build(arr, 0, 0, tree_size);
    }

    int less(int l, int r, int x, int node, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return 0;
        if (lx >= l && rx <= r)
        {
            return lower_bound(SegData[node].ar.begin(), SegData[node].ar.end(), x) - SegData[node].ar.begin();
        }

        int mid = (lx + rx) / 2;
        int lf = less(l, r, x, 2 * node + 1, lx, mid);
        int ri = less(l, r, x, 2 * node + 2, mid, rx);
        return lf + ri;
    }

    int less(int l, int r, int x)
    {
        return less(l, r, x, 0, 0, tree_size);
    }

    int greater(int l, int r, int x, int node, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return 0;
        if (lx >= l && rx <= r)
        {
            return SegData[node].ar.end() - upper_bound(SegData[node].ar.begin(), SegData[node].ar.end(), x);
        }

        int mid = (lx + rx) / 2;
        int lf = greater(l, r, x, 2 * node + 1, lx, mid);
        int ri = greater(l, r, x, 2 * node + 2, mid, rx);
        return lf + ri;
    }

    int greater(int l, int r, int x)
    {
        return greater(l, r, x, 0, 0, tree_size);
    }

    int sumless(int l, int r, int x, int node, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return 0;
        if (lx >= l && rx <= r)
        {
            int idx = lower_bound(SegData[node].ar.begin(), SegData[node].ar.end(), x) - SegData[node].ar.begin();
            if(idx > 0){
                return SegData[node].pref[idx-1];
            }else 
                return 0;
        }

        int mid = (lx + rx) / 2;
        int lf = sumless(l, r, x, 2 * node + 1, lx, mid);
        int ri = sumless(l, r, x, 2 * node + 2, mid, rx);
        return lf + ri;
    }

    int sumless(int l, int r, int x)
    {
        return sumless(l, r, x, 0, 0, tree_size);
    }
    int sumgreater(int l, int r, int x, int node, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return 0;
        if (lx >= l && rx <= r)
        {
            int idx = upper_bound(SegData[node].ar.begin(), SegData[node].ar.end(), x) - SegData[node].ar.begin();
            if (idx > 0)
            {
                return SegData[node].pref[SegData[node].pref.size() - 1] - SegData[node].pref[idx - 1];
            }
            else
                return SegData[node].pref[SegData[node].pref.size() - 1];
        }

        int mid = (lx + rx) / 2;
        int lf = sumgreater(l, r, x, 2 * node + 1, lx, mid);
        int ri = sumgreater(l, r, x, 2 * node + 2, mid, rx);
        return lf + ri;
    }

    int sumgreater(int l, int r, int x)
    {
        return sumgreater(l, r, x, 0, 0, tree_size);
    }

    pair<int, int> get_range(int l, int r, int node, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return {0, 1e8};

        if (lx >= l && rx <= r)
            return {SegData[node].mx, SegData[node].mn};

        int mid = (lx + rx) / 2;
        auto [lfmx, lfmn] = get_range(l, r, 2 * node + 1, lx, mid);
        auto [rimx, rimn] = get_range(l, r, 2 * node + 2, mid, rx);

        return {max(lfmx, rimx), min(lfmn, rimn)};
    }
    // r is execlusive
    pair<int, int> get_range(int l, int r)
    {
        return get_range(l, r, 0, 0, tree_size);
    }
};


int main (){
    vector<int> ar = {3,5,1,3,6,6,1,61,6,82,552,31,11,5,6,7,1,9} ;

    SegTree segtree(ar);

    cout <<  segtree.sumgreater(0,6 , 0) ;

}