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
int N = 5000002 , loog = 40;
using namespace std;
using namespace __gnu_pbds;
#define int long long
// #define int uint64_t
// #define u128 __uint128_t


struct TreeNode {
    int sum = 0, lazy = 0, isLazy = 0;
    TreeNode *left = nullptr, *right = nullptr;

    TreeNode() {}
    TreeNode(int x): sum(x) {}
    TreeNode(TreeNode *&a, TreeNode *&b): left(a), right(b) {}

    void update(int x, ll lx, ll rx) {
        sum += 1ll * x * ((rx - lx) % mod) % mod;
        sum%=mod;
        lazy += x, isLazy = 1;
        lazy%=mod;
    }
};

using Node = TreeNode*;

struct DynamicSagara {
    Node root = new TreeNode();
    const ll n;

    DynamicSagara(ll n): n(n) {}

    void propagate(Node &cur, ll lx, ll rx) {
        ll m = (lx + rx) / 2;
        if (cur->left == nullptr) cur->left = new TreeNode(); // l -> m
        if (cur->right == nullptr) cur->right = new TreeNode(); // m -> r
        if (!cur->isLazy) return;

        cur->left->update(cur->lazy, lx, m);
        cur->right->update(cur->lazy, m, rx);

        cur->lazy = cur->isLazy = 0;
    }

    void update(ll &l, ll &r, int &val, Node &node, ll lx, ll rx) {
        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) return node->update(val, lx, rx);
        propagate(node, lx, rx);

        ll m = (lx + rx) / 2;
        update(l, r, val, node->left, lx, m);
        update(l, r, val, node->right, m, rx);

        node->sum = (node->left->sum + node->right->sum);
        if(node->sum >= mod) node->sum -= mod;
    }

    ll query(ll l, ll r, Node &node, ll lx, ll rx) {
        if (lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) return node->sum;
        propagate(node, lx, rx);

        ll m = (lx + rx) / 2;
        ll ans = query(l, r, node->left, lx, m);
        ans += query(l, r, node->right, m, rx);
        if(ans >= mod) ans -= mod;
        return ans;
    }

    void update(ll l, ll r, int val) { update(l, r, val, root, 0, n); }

    ll query(ll l, ll r) { return query(l, r, root, 0, n); }
};


// another implementation single update range query for multiplication
struct TreeNode {
    int sum = 0, lazy = 0, isLazy = 0;
    TreeNode *left = nullptr, *right = nullptr;

    TreeNode() {}
    TreeNode(int x): sum(x) {}
    TreeNode(TreeNode *&a, TreeNode *&b): left(a), right(b) {}

};

using Node = TreeNode*;

struct DynamicSagara {
    Node root = new TreeNode();
    const ll n;

    DynamicSagara(ll n): n(n) {}


    void add(ll &idx, int &val, Node &node, ll lx, ll rx) {
        if (!node)
            node = new TreeNode();
        if (rx - lx == 1)
        {
            node->sum += val;
            node->sum%=mod;
            return;
        }

        int mid = (lx + rx) / 2;
        if (idx < mid)
            add(idx, val, node->left , lx, mid);

        else
            add(idx, val, node->right, mid, rx);

        node->sum =
        ((node->left ? node->left->sum : 0) *
         (node->right ? node->right->sum : 0)) % mod;
    }

    ll query(ll l, ll r, Node &node, ll lx, ll rx) {
        if (lx >= r || rx <= l ) return 1;
        if (!node)return 0 ;
        if (lx >= l && rx <= r) return node->sum;

        ll m = (lx + rx) / 2;
        ll ans = query(l, r, node->left, lx, m);
        ans *= query(l, r, node->right, m, rx);
        ans%=mod;
        return ans;
    }

    void add(ll idx, int val) { add(idx, val, root, 0, n); }

    ll query(ll l, ll r) { return query(l, r, root, 0, n); }
};