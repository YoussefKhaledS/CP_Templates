


// Quotient grouping: group ranges where floor(n/i) is the same.
// Example n=10: [4,5] -> 10/i = 2, [6,10] -> 10/i = 1.
// Reduces O(n) iterations to O(sqrt(n)).
void floordivisiongrouping() {
    int n ;

    vector<array<int,3>> ar ;
    for (int i = 1 ; i<= n ;) {
        int value = n/i ;
        int end = n/value;

        ar.push_back({i, end, value}) ;
        i = end+1;
    }

}
