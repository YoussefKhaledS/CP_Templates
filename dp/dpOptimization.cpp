
// when using the % in one of dp state you need to make sure that the currently computed state is reset
/*
*    int dp[2][k+2] ;
    memset(dp, 0 , sizeof dp) ;
    dp[1][0] = 1;

    for (int i = n-1; ~i ;i--) {
        memset(dp[i&1], 0, sizeof(dp[i&1]));
        for (int rem = 0 ; rem <= k ; rem++) {
            for (int j = 0 ; j <= min(rem , ar[i]); j++) {
                dp[i&1][rem] += dp[(i+1)&1][rem-j] ;
            }
        }
    }
 */

