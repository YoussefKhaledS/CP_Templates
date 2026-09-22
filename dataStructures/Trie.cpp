//
// Created by youssef khaled on 9/14/2026.
//
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
int N = 7e5+3, loog = 40;
using namespace std;
using namespace __gnu_pbds;
#define int long long

// Node doesn't store its char; nxt[i] represents the edge labeled 'a' + i
// Example: nxt[2] = 5 means: current node --'c'--> node 5
// For arbitrary characters or a huge alphabet, a map/hashmap can be used instead.
struct Trie {
    struct Node {
        int nxt[26]; // store the index of the child node from using char i
        bool end; // does  the string ends here
        int freq;
        int pref;// number of inserted strings having this prefix

        Node() {
            memset(nxt, -1, sizeof nxt) ;
            end = false ;
            freq = 0 ;
            pref= 0 ;
        }
    };

    vector<Node> tree;

    Trie() {
        tree.push_back(Node());// root node
    }

    void insert(string s) {
        int cur = 0 ; //start at the root node

        for (char c: s) {
            int x = c - 'a' ;

            if (tree[cur].nxt[x] == -1) {
                tree[cur].nxt[x] = tree.size() ;// the index of the node we will add
                tree.push_back(Node()); // the newly added node
            }

            cur = tree[cur].nxt[x];
            tree[cur].pref++;
        }
        tree[cur].end= true;
        tree[cur].freq++;// add occurrence of this string
    }
    // use prefix = 1 to ask for prefix exist and 0 to ask for a word
    int countWordorprefix(string s, bool prefix) {
        int cur = 0 ;

        for (char c : s) {
            int x = c- 'a' ;

            if (tree[cur].nxt[x] == -1)return 0 ;

            cur = tree[cur].nxt[x] ;
        }
        if (prefix)return tree[cur].pref;
        return tree[cur].freq ;
    }

    void remove(string s) {
        int cur = 0 ;

        for (char c: s) {
            int x = c - 'a' ;

            if (tree[cur].nxt[x] == -1)return ;
            cur = tree[cur].nxt[x];

            tree[cur].pref--;
        }

        if (--tree[cur].freq == 0)
            tree[cur].end = false ;
    }

    void clear() {
        tree.clear();
        tree.push_back(Node());
    }
};




// solution for : return the most occurence word with this prefix https://www.spoj.com/problems/TRYCOMP/
struct Trie {
    struct Node {
        int nxt[26]; // store the index of the child node from using char i
        bool end; // does  the string ends here
        int freq;

        string answord;
        int anscnt ;

        Node() {
            memset(nxt, -1, sizeof nxt) ;
            end = false ;
            answord = "" ;
            anscnt = 0 ;
            freq = 0 ;
        }
    };

    vector<Node> tree;

    Trie() {
        tree.push_back(Node());// root node
    }

    void insert(string s) {
        int cur = 0 ; //start at the root node

        for (char c: s) {
            int x = c - 'a' ;

            if (tree[cur].nxt[x] == -1) {
                tree[cur].nxt[x] = tree.size() ;// the index of the node we will add
                tree.push_back(Node()); // the newly added node
            }

            cur = tree[cur].nxt[x];
        }
        tree[cur].end= true;
        tree[cur].freq++;// add occurrence of this string
        int wordfreq = tree[cur].freq;

        cur = 0 ;
        for (char c: s) {
            int x = c - 'a';

            if (tree[cur].anscnt < wordfreq) {
                tree[cur].anscnt = wordfreq;
                tree[cur].answord= s;
            }else if  (tree[cur].anscnt == wordfreq) {
                tree[cur].answord = min(s, tree[cur].answord) ;
            }

            cur = tree[cur].nxt[x] ;
        }
        if (tree[cur].anscnt < wordfreq) {
            tree[cur].anscnt = wordfreq;
            tree[cur].answord= s;
        }else if  (tree[cur].anscnt == wordfreq) {
            tree[cur].answord = min(s, tree[cur].answord) ;
        }

    }
    // use prefix = 1 to ask for prefix exist and 0 to ask for a word
    pair<string , int> countWordorprefix(string s, bool prefix) {
        int cur = 0 ;

        for (char c : s) {
            int x = c- 'a' ;

            if (tree[cur].nxt[x] == -1)return {"", 0} ;

            cur = tree[cur].nxt[x] ;
        }
        if (prefix)return {tree[cur].answord, tree[cur].anscnt};
    }

};

// binary trie
// notes : to get max xor for subarray just make prefix xor array and use the template itrative
struct Trie {
    int LOG = 40 ;
    struct Node {
        int nxt[2]; // store the index of the child node from using char i
        int pref;// number of inserted strings having this prefix

        Node() {
            memset(nxt, -1, sizeof nxt) ;
            pref= 0 ;
        }
    };

    vector<Node> tree;

    Trie() {
        tree.push_back(Node());// root node
    }

    void insert(int n) {
        int cur = 0 ; //start at the root node

        for (int i = LOG; i>= 0 ;i--){
            int bit = (1ll<<i) & n ;
            bool on = bit ;

            if (tree[cur].nxt[on] == -1) {
                tree[cur].nxt[on] = tree.size() ;// the index of the node we will add
                tree.push_back(Node()); // the newly added node
            }

            cur = tree[cur].nxt[on];
            tree[cur].pref++;
        }
    }
    // use prefix = 1 to ask for prefix exist and 0 to ask for a word
    int maxxor(int x) {// get max xor beetween intered x and one of the numbers insdie the DS
        // for this funciton to work with empty you need to insert 0 before anything
        int cur = 0 ;
        int ans = 0 ;

        for (int i = LOG ;i >= 0 ;i--) {
            int bit = (1ll<<i) & x ;
            bool on = bit ;

            int nxtcurx = tree[cur].nxt[!on] ;
            int nxtcury = tree[cur].nxt[on] ;

            if (nxtcurx != -1 && tree[nxtcurx].pref != 0) {// !bit does exist in the trie
                ans|=(1ll << i);
                cur = nxtcurx;
            }else {
                cur = nxtcury ;
            }
        }
        return ans;
    }

    void remove(int x) {
        int cur = 0 ;

        for (int i = LOG; i>= 0 ;i--){
            int bit = (1ll<<i) & x ;
            bool on = bit ;

            cur = tree[cur].nxt[on];

            tree[cur].pref--;
        }
    }
};


// Bitwise trie: pref = subtree frequency; count y with (x ^ y) <= k.
struct Trie {
    int LOG = 40 , k;
    struct Node {
        int nxt[2]; // store the index of the child node from using char i
        ll pref;// number of inserted strings having this prefix
        int idx ;

        Node() {
            memset(nxt, -1, sizeof nxt) ;
            pref= 0 ;
            idx = -1 ;
        }
    };

    vector<Node> tree;

    Trie(int _k) {
        tree.push_back(Node());// root node
        k = _k ;
    }

    void insert(int n, int idx) {
        int cur = 0 ; //start at the root node

        for (int i = LOG; i>= 0 ;i--){
            int bit = (1ll<<i) & n ;
            bool on = bit ;

            if (tree[cur].nxt[on] == -1) {
                tree[cur].nxt[on] = tree.size() ;// the index of the node we will add
                tree.push_back(Node()); // the newly added node
            }

            cur = tree[cur].nxt[on];
            tree[cur].pref++;
        }
        tree[cur].idx = max(tree[cur].idx, idx);
    }

    ll cntranges(int x) {
        int cur = 0 ;
        ll ans = 0 ;

        for (int i = LOG ;i >= 0 ;i--) {
            int bit = (1ll<<i) & x;
            int bitK = (1ll<<i) & k ;
            bool on = bit ;

            int nxtNode = tree[cur].nxt[on] ;
            int nxtNotNode = tree[cur].nxt[!on] ;

            bool res1 =( nxtNotNode != -1 && tree[nxtNotNode].pref != 0)  ;
            bool res0 = (nxtNode != -1 && tree[nxtNode].pref != 0) ;

            if (bitK) {
                if (res1)cur = nxtNotNode ;
                else return ans ;
            }else {// bit k is 0
                if (res1) {
                    ans+= tree[nxtNotNode].pref;
                }
                if (res0)cur = nxtNode;
                else return ans;
            }
        }
        return ans + tree[cur].pref ;
    }
};
