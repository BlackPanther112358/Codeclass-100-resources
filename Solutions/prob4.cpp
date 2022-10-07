#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // Taking the input from judge

    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];

    // States: Originally dp[i][x], number of ways possible where,
    // 0 <= i < n, i represents the ith index
    // 0 <= x <= m, x represents the value at current index
    // We will further state optimize the DP array to only store values of all x for the previous index
    // Setting up the DP array

    vector<long long int> dp(m, 0);  // Only need to store number of ways upto previous index (Space Optimisation)

    // Initialise the DP table
    // If the first value is known, then set that state to 1, else set all the states to 1
    if(arr[0] == 0) for(int i = 0; i < m; i++) dp[i] = 1;
    else dp[arr[0] - 1] = 1;

    // We iterate from first index to last index
    for(int i = 1; i < n; i++){
        // Initialize a temporary array to store the values for current index
        vector<long long int> temp(m, 0);
        
        // Tranisition: dp[i][x] = dp[i - 1][x - 1] + dp[i - 1][x] + dp[i - 1][x + 1];
        // if the value at ith index is unknown
        if(arr[i] == 0){
            for(int j = 0; j < m; j++){
                temp[j] = dp[j];
                if(j > 0) temp[j] += dp[j - 1];
                if(j < (m - 1)) temp[j] += dp[j + 1];
                temp[j] %= mod;
            }
        }else{
            temp[arr[i] - 1] = dp[arr[i] - 1];
            if(arr[i] > 1) temp[arr[i] - 1] += dp[arr[i] - 2];
            if(arr[i] < m) temp[arr[i] - 1] += dp[arr[i]];
            temp[arr[i] - 1] %= mod;
        }

        // Update the values of the dp table from temp
        dp = temp;
    }

    // Output the sum of all values in the dp table
    long long int ans = 0;
    for(int i = 0; i < m; i++) ans += dp[i];
    ans %= mod;
    cout << ans;

    // Time Complexity : O(n*m)
    // Space Complexity : O(m)

    return 0;
}