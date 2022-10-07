#include <bits/stdc++.h>
using namespace std;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // NOTE: This problem is called Knapsack problem and is quite famous DP problem.
    // This algorithm is an example of pseudo-polynomial algorithms

    // Taking the input from judge

    int n, w;
    cin >> n >> w;

    vector<vector<int>> arr(n, vector<int> (2));
    for(int i = 0; i < n; i++){
        cin >> arr[i][0] >> arr[i][1];
    }

    // States: Originally dp[i][x], maximum points possible where,
    // 0 <= i < n, i represents the ith item
    // 0 <= x <= w, x represents weight of the knapsack
    // We will further state optimize the DP array to only store values of all x for the previous item
    // Setting up the DP array

    vector<long long int> dp(w + 1, 0);  // Only need to store number of ways upto previous item (Space Optimisation)

    // We iterate from first item to last item
    for(int i = 0; i < n; i++){
        // Initialize a temporary array to store the values for current item
        vector<long long int> temp = dp;
        for(int j = w; j >= 0; j--){
            if(j < arr[i][0]) break;
            // Tranisition: dp[i][x + weight[i]] = value[i] + dp[i - 1][x];
            temp[j] = max(temp[j], arr[i][1] + dp[j - arr[i][0]]); 
        }
        // Update the values of the dp table from temp
        dp = temp;
    }

    // Output the maximum value possible
    long long int ans = 0;
    for(int i = 0; i <= w; i++) ans = max(ans, dp[i]);
    cout << ans;

    // Time Complexity : O(n*w)
    // Space Complexity : O(w)

    return 0;
}