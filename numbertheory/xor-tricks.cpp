#include <bits/stdc++.h>
using namespace std;

#define ll long long

/// note this file is generated using ChatGpt do not copy past any of it
/*
====================================================
                XOR TRICKS CHEATSHEET
====================================================

Core Properties:
x ^ x = 0
x ^ 0 = x
XOR is commutative and associative

Main Idea:
Even occurrences cancel out.
Odd occurrences remain.
*/

/*==================================================
    1. PREFIX XOR FROM 0 -> n
    Pattern repeats every 4
==================================================*/

int xor_0_to_n(int n) {
    if (n % 4 == 0) return n;
    if (n % 4 == 1) return 1;
    if (n % 4 == 2) return n + 1;
    return 0;
}

/*
n % 4:
0 -> n
1 -> 1
2 -> n+1
3 -> 0
*/

/*==================================================
    2. XOR RANGE [L -> R]
==================================================*/

int xor_L_to_R(int l, int r) {
    return xor_0_to_n(r) ^ xor_0_to_n(l - 1);
}

/*==================================================
    3. FIND SINGLE NUMBER
    All appear twice except one
==================================================*/

int singleNumber(vector<int>& a) {
    int ans = 0;

    for (int x : a)
        ans ^= x;

    return ans;
}

/*==================================================
    4. FIND MISSING NUMBER [1 -> n]
==================================================*/

int missingNumber(vector<int>& a, int n) {
    int ans = 0;

    for (int i = 1; i <= n; i++)
        ans ^= i;

    for (int x : a)
        ans ^= x;

    return ans;
}

/*==================================================
    5. FIND DUPLICATE NUMBER
==================================================*/

int duplicateNumber(vector<int>& a, int n) {
    int ans = 0;

    for (int i = 1; i <= n; i++)
        ans ^= i;

    for (int x : a)
        ans ^= x;

    return ans;
}

/*==================================================
    6. FIND TWO UNIQUE NUMBERS
    Others appear twice
==================================================*/

pair<int,int> twoUnique(vector<int>& a) {

    int xr = 0;

    for (int x : a)
        xr ^= x;

    // Lowest differing bit
    int bit = xr & (-xr);

    int u = 0, v = 0;

    for (int x : a) {

        if (x & bit)
            u ^= x;
        else
            v ^= x;
    }

    return {u, v};
}

/*==================================================
    12. REMOVE LOWEST SET BIT
==================================================*/

int removeLowestSetBit(int x) {
    return x & (x - 1);
}

/*==================================================
    15. CHECK POWER OF TWO
==================================================*/

bool isPowerOfTwo(int x) {
    return x > 0 && !(x & (x - 1));
}

/*==================================================
    16. GRAY CODE
==================================================*/

/*
Gray Code:
Adjacent numbers differ by only ONE bit.

Example:
0 -> 000
1 -> 001
2 -> 011
3 -> 010

Useful in:
- hardware
- minimizing bit transitions
- some graph problems

Formula:
gray = n ^ (n >> 1)

Idea:
XOR current bits with shifted version.
*/

int grayCode(int n) {
    return n ^ (n >> 1);
}

/*==================================================
    17. SUBARRAY XOR = K
==================================================*/

/*
Exactly like prefix sums.

If:
pref[j] ^ pref[i-1] = k

Then:
pref[i-1] = pref[j] ^ k

So for every prefix XOR:
we search for an older prefix that differs by k.

freq stores:
how many times each prefix XOR appeared.

Complexity:
O(n log n) with map
O(n) with unordered_map
*/

int subarrayXorK(vector<int>& a, int k) {

    map<int,int> freq;

    freq[0] = 1;

    int pref = 0;
    int ans = 0;

    for (int x : a) {

        pref ^= x;

        // previous prefix needed
        ans += freq[pref ^ k];

        freq[pref]++;
    }

    return ans;
}

/*==================================================
    18. MAXIMUM XOR PAIR (TRIE)
==================================================*/

/*
Goal:
maximize ai ^ aj

Observation:
To maximize XOR:
prefer opposite bits.

Example:
1 ^ 0 = 1  (good)
0 ^ 1 = 1  (good)

Trie stores binary representation.

For every bit:
- if current bit is 0
  prefer 1
- if current bit is 1
  prefer 0

Greedy works because higher bits
have larger contribution.

Complexity:
Insert: O(32)
Query : O(32)
*/

struct Node {
    Node* nxt[2] = {};
};

struct Trie {

    Node* root = new Node();

    void insert(int x) {

        Node* cur = root;

        for (int i = 31; i >= 0; i--) {

            int bit = (x >> i) & 1;

            if (!cur->nxt[bit])
                cur->nxt[bit] = new Node();

            cur = cur->nxt[bit];
        }
    }

    int maxXor(int x) {

        Node* cur = root;

        int ans = 0;

        for (int i = 31; i >= 0; i--) {

            int bit = (x >> i) & 1;

            // Prefer opposite bit
            if (cur->nxt[1 - bit]) {

                ans |= (1 << i);

                cur = cur->nxt[1 - bit];
            }
            else {
                cur = cur->nxt[bit];
            }
        }

        return ans;
    }
};

/*==================================================
    19. XOR BASIS (LINEAR BASIS)
==================================================*/

/*
Advanced CP structure.

Stores independent XOR vectors.

Similar idea to Gaussian elimination,
but for XOR instead of addition.

Main Uses:
- maximum subset XOR
- kth XOR value
- xor path problems
- xor cycles in graphs

Key Idea:
Each basis[i] owns highest bit i.

While inserting:
remove highest bits using existing basis.

If number becomes 0:
it was representable already.

maxXor():
greedily try improving answer.

Complexity:
O(LOG)
*/

struct XorBasis {

    static const int LOG = 60;

    ll basis[LOG] = {};

    void insert(ll x) {

        for (int i = LOG - 1; i >= 0; i--) {

            if (!(x & (1LL << i)))
                continue;

            // Empty position
            if (!basis[i]) {
                basis[i] = x;
                return;
            }

            // Remove highest bit
            x ^= basis[i];
        }
    }

    // Maximum XOR subset
    ll maxXor() {

        ll ans = 0;

        for (int i = LOG - 1; i >= 0; i--)
            ans = max(ans, ans ^ basis[i]);

        return ans;
    }
};

/*==================================================
    20. NIM GAME
==================================================*/

/*
Classic game theory XOR problem.

Players remove stones from piles.

Rule:
If total XOR == 0
current player loses.

If total XOR != 0
current player can force win.

Why?
Winning move always exists that
makes XOR become 0.

Very important theorem in CP.

Foundation of:
- Nim
- Sprague Grundy
- impartial games
*/

bool firstPlayerWins(vector<int>& piles) {

    int xr = 0;

    for (int x : piles)
        xr ^= x;

    return xr != 0;
}

/*==================================================
                    MAIN
==================================================*/

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}