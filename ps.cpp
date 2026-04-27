#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define youssef                   \
    ios_base::sync_with_stdio(0); \
    cin.tie(0), cout.tie(0);
#define el '\n'
#define EL '\n'
#define ll long long
#define yes "YES"
#define no "NO"
const ll mod = 1e9 + 7, infi = LONG_MAX;
int N = 5e5;
using namespace std;
#define int long long

using namespace __gnu_pbds;

typedef tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update> orderedset;
// find_by_order(k) : itrator of k-th smallest element 
// order_of_key(x) : number of element less than x

// merge segtree
struct Node
{
    vector<int> ar, pref;
    int mx, mn;
    Node()
    {
        ar = {};
        pref = {};
        mx = 0;
        mn = infi;
    }
    Node(vector<int> _ar)
    {
        ar = _ar;
        pref = _ar;
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

        for (int i = 0; i < n + m; i++)
        {
            ans.pref[i] = (i != 0) ? ans.pref[i - 1] + ans.ar[i] : ans.ar[i];
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
            if (idx > 0)
            {
                return SegData[node].pref[idx - 1];
            }
            else
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
                return SegData[node].pref[SegData[node].pref.size() -1] - SegData[node].pref[idx - 1];
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
};

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> ar(n);
    for (int i = 0; i < n; i++)
        cin >> ar[i];

    orderedset os;

    // insert first window
    for (int i = 0; i < k; i++)
    {
        os.insert({ar[i], i});
    }

    for (int i = 0; i + k <= n; i++)
    {
        int cnt = k;

        int midean = os.find_by_order((cnt - 1) / 2)->first;

        


        if (i + k < n)
        {
            os.erase({ar[i], i});
            os.insert({ar[i + k], i + k}); 
        }
    }
}

signed main()
{
    youssef;
    int ts = 1;

    // cin >> ts;
    for (int i = 1; i <= ts; i++)
    {
        solve();
        // cout << el;
    }
}