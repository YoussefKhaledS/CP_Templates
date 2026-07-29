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
    orderedmultiset os;
    os.insert({36, 0}) ;
    os.insert({3,1}) ;
    os.insert({32, 2}) ;
    os.insert({32, 7}) ;
    os.insert({31, 3}) ;
    os.insert({30, 4}) ;
    os.insert({99, 5}) ;
    os.insert({35, 6}) ;

    // for(auto [i, x]: os){
    //     cout << i << ' ' ;
    // }
    auto it = os.lower_bound({32,-1}) ;
    if (it != os.end()) {
        cout << (it)->first ;
    }

    cout << '\n' ;
    cout << os.order_of_key({2,8})  ;

}