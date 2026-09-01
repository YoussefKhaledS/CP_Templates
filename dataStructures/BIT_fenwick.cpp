#include <bits/stdc++.h>

using namespace std; 
// Input vector: 0-indexed
// BIT operations: 1-indexed


struct BIT {
    int n ;
    vector<int> b ;

    BIT(int _n){
        n= 1 ;
        while(n < _n)n<<=1;
        b.assign(n+1 ,0) ;
    }

    BIT(vector<int> &a): BIT(a.size()) {
        for (int i = 0 ; i < a.size() ;i++) {
            add(i+1, a[i]);
        }
    }

    int merge(int a, int b){
        return a + b;
    }
    int inverse_merge(int a, int b){
        return a - b;
    }

    int get(int idx){
        int ret = 0 ;
        while(idx){
            ret = merge(ret , b[idx]) ;
            idx -= idx & -idx ; 
        }
        return ret ; 
    }

    void add(int idx, int v){
        while(idx <= n){
            b[idx] = merge(b[idx] , v) ;
            idx+= idx&-idx ;
        }
    }

    int get(int l, int r){
        return inverse_merge(get(r) , get(l-1)) ;
    }

    int get_idx(int idx){
        return inverse_merge(get(idx) , get(idx -1)) ;
    }

    void set(int idx, int v){
        int old = get_idx(idx) ;
        add(idx, -old + v) ;
    }

    int lower_bound(int sum){
        int idx = 0 ; 
        for(int step = n; step > 0; step >>= 1){
            if(b[idx + step] < sum){ // if you want to make it upper bound chenge condition to <= 
                sum = inverse_merge(sum, b[idx+step]) ;
                idx+=step;
            }
        }
        return idx+1 ;
    }

    int size(){
        return b[n] ;
    }

};

int main(){
    cout << "abc" ;
}
