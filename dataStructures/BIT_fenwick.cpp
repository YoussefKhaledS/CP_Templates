#include <bits/stdc++.h>

using namespace std; 

struct BIT {
    int n ;
    vector<int> b ;

    BIT(int _n){
        n= 1 ;
        while(n < _n)n<<=1;
        b.assign(n+1 ,0) ;
    }

    int get(int idx){
        int ret = 0 ;
        while(idx){
            ret+=b[idx] ;
            idx -= idx & -idx ; 
        }
        return ret ; 
    }

    void add(int idx, int v){
        while(idx <= n){
            b[idx]+=v;
            idx+= idx&-idx ;
        }
    }

    int get(int l, int r){
        return get(r) - get(l-1) ;
    }

    int get_value(int idx){
        return get(idx) - get(idx -1) ;
    }

    void set(int idx, int v){
        int old = get_value(idx) ;
        add(idx, -old + v) ;
    }

    int lower_bound(int sum){
        int idx = 0 ; 
        for(int step = n; step > 0; step >>= 1){
            if(b[idx + step] < sum){ // if you want to make it upper bound chenge condition to <= 
                sum-=b[idx+step] ;
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
