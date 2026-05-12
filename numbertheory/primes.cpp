#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define youssef ios_base::sync_with_stdio(0); cin.tie(0), cout.tie(0);
#define el '\n'
#define EL '\n'
#define yes "YES"
#define no "NO"
#define ll long long
const ll mod = 998244353 , infi = LONG_MAX;
int N = 5e5 , loog = 30;
using namespace std;
#define  int long long

vector<bool> sieve(int n) {// O(nloglog(n))
    vector<bool> isprime(n+1, 1);

    isprime[0] = isprime[1] = false ;

    for (int i = 2 ; i*i <= n ;i++) {
        if (isprime[i]) {
            for (int j = i*i ; j<= n ; j+=i)
                isprime[j]= false;
        }
    }

    return isprime ;
}

vector<int> spf(N) ;
void buildSPF(int n) {
    for (int i = 1; i<= n ; i++)spf[i] = i ;

    for (int i =2 ; i*i <= n ;i++) {
        if (spf[i] == i) {
            for (int j = i*i ; j <= n ; j+=i) {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
}

vector<int> factorize(int x) {// get prime factors in log(n)
    vector<int> fac;

    while (x> 1) {
        fac.push_back(spf[x]) ;
        x/=spf[x];
    }
    return fac;
}

// can be used to konow if perfect square(exps even) or cube(exps % 3 == 0)
vector<int> getfactors(int n ) {//O(sqrt(n))
    vector<int> ar;

    for (int x = 2 ; x*x <= n ;x++) {
        while (n % x  == 0) {
            ar.push_back(x) ;
            n/=x;
        }
    }
    if (n>1)
        ar.push_back(n) ;

    return ar ;
}
vector<int> num_of_divisors(int n){
    vector<int> divs(n,0) ;

    for(int i =1 ; i< n ;i++){
        for(int j = i; j < n ;j+=i){
            divs[j]++;
        }
    }
    return divs;
}
vector<int> sum_of_divisors(int n){
    vector<int> divs(n,0) ;

    for(int i =1 ; i< n ;i++){
        for(int j = i; j < n ;j+=i){
            divs[j]+=i;
        }
    }
    return divs;
}



signed main() {
    ll x = 1 ;
    for (int i = 234 ; i>= 229 ; i--) {
        x*=i ;
        vector<int> factors = getfactors(i) ;


        for (auto j: factors)cout << j<< ' ' ;cout << el;
    }
    cout << x <<el;
    vector<int> factors = getfactors(6) ;
    // 18,838,314,540,045

    for (auto j: factors)cout << j<< ' ' ;cout << el;
}
























