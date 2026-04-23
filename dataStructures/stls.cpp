#include <bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> orderedset;
// find_by_order(k) : itrator of k-th smallest element
// order_of_key(x) : number of element less than x


// ordered multiset (allows duplicates)
typedef tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update> orderedmultiset;
// use pair {value, unique_id} to allow duplicates


int main(){
    orderedset os;
    os.insert(3) ;
    os.insert(36) ;
    os.insert(32) ;
    os.insert(31) ;
    os.insert(30) ;
    os.insert(99) ;
    os.insert(35) ;

    for(auto i: os){
        cout << i << ' ' ;
    }

    cout << '\n' ;
    cout << *os.find_by_order(3)  ;

}