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


struct Node {
    int mx = -infi, mn = infi, val ;
    Node(): val(0){}
    Node(int x): mx(x), mn(x), val(x) {}
};
struct MonoQueue {

    stack<Node> a,b;

    int size(){return a.size()+b.size();}

    void merge(Node &a, Node &b) {
        a.mn = min(a.mn, b.mn) ;
        a.mx = max(a.mx, b.mx) ;
    }

    void push(int val) {
        Node nd = Node(val);
        if (!a.empty())merge(nd, a.top()) ;
        a.push(nd) ;
    }

    void move() {
        while (!a.empty()) {
            Node nd = Node(a.top().val) ;
            if (!b.empty())merge(nd, b.top());
            b.push(nd) , a.pop() ;
        }
    }

    Node get() {
        Node res;
        if (!b.empty())merge(res, b.top());
        if (!a.empty())merge(res, a.top());
        return res ;
    }

    Node pop() {
        Node res ;
        if (b.empty())move();
        if (!b.empty())res = b.top(), b.pop();
        return res ;
    }
};