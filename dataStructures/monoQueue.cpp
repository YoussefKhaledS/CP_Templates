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




/*
    MonoQueue (Queue with Aggregates)

    Complexity:
    - push() : O(1) amortized
    - pop()  : O(1) amortized
    - get()  : O(1)

    Supports any associative merge operation.
    Examples:
    - min
    - max
    - min & max together
    - gcd
    - bitwise AND/OR
    - xor
    - custom monoids

    Advantages over deque:
    + Works for ANY associative operation (not only monotonic ones).
    + Can return multiple aggregates at once (min, max, gcd, ...).
    + Simple generic implementation.
    + No need to maintain monotonicity manually.

    Typical uses:
    - Sliding window minimum/maximum.
    - Fixed-size window aggregate queries.
    - DP with sliding windows.
    - Two pointers when window aggregate is needed.
    - Binary search on answer + window checking.

    Idea:
    - Two stacks.
    - Each stack stores prefix aggregates.
    - Queue aggregate = merge(left stack aggregate, right stack aggregate).

    Requirement:
    merge(a, b) must be associative:
        merge(merge(a,b),c) == merge(a,merge(b,c))

    How to Use: 
        1) Push new elements into the window: mq.push(a[i]);
        2) Query the current aggregate: auto cur = mq.get(); cur.mn // minimum cur.mx // maximum
        3) Remove the oldest element when the window moves: mq.pop();
        4) Current window size: mq.size();
*/