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

struct Node {
    int left = 0, right = 0, val = 0;
    Node(){}
    Node (int v) : val(v){}
    void upd(int v) {
        val = v;
    }
};

struct PST {

    vector<Node> nodes;
    int tree_size;

    PST(int n) {
        tree_size = n;
        nodes.reserve(1e7);
    }

    void merge(Node &ans, const Node & lf, const Node & ri) {
        ans.val = lf.val + ri.val;
    }

    int create_node() {
        nodes.push_back({});
        return nodes.size() - 1;
    }

    int init(vector<int> &arr, int lx, int rx) {
        int id = create_node();
        if(rx - lx == 1) {
            nodes[id].val = arr[lx];
            return id;
        }

        int mid = (lx + rx) >> 1;

        nodes[id].left = init(arr, lx, mid);
        nodes[id].right = init(arr, mid, rx);
        merge(nodes[id], nodes[nodes[id].left], nodes[nodes[id].right]);

        return id;
    }

    int init(vector<int> & arr) {
        return init(arr, 0, tree_size);
    }

    int set(int idx, int val, int ni, int lx, int rx) {
        int id = create_node();
        if(rx - lx == 1) {
            nodes[id] = Node(val);
            return id;
        }

        int mid = (lx + rx) >> 1;

        nodes[id].left = nodes[ni].left;
        nodes[id].right = nodes[ni].right;

        if(idx < mid)
            nodes[id].left = set(idx, val, nodes[ni].left, lx, mid);
        else
            nodes[id].right = set(idx, val, nodes[ni].right, mid, rx);

        merge(nodes[id], nodes[nodes[id].left], nodes[nodes[id].right]);
        return id;
    }

    int set(int idx, int val, int version) {
        return set(idx, val, version, 0, tree_size);
    }

    Node get(int l, int r, int ni, int lx, int rx) {
        if(lx >= r || rx <= l)
            return Node();
        if(lx >= l && rx <= r)
            return nodes[ni];

        int mid = (lx + rx) >> 1;

        Node ans = Node();
        merge(ans, get(l, r, nodes[ni].left, lx, mid), get(l, r, nodes[ni].right, mid, rx));
        return ans;
    }
    int get(int l, int r, int version) {
        return get(l, r, version, 0, tree_size).val;
    }
};
