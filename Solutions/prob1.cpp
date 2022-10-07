#include <bits/stdc++.h>
using namespace std;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // Taking the input from judge

    int n;
    cin >> n;

    vector<vector<int>> points(n, vector<int> (3));
    for(int i = 0; i < n; i++){
        cin >> points[i][0] >> points[i][1] >> points[i][2];
    }

    // States: Originally dp[i][x] stores the maximum possible value possible afterwards, where,
    // 0 <= i < n, i represents the ith day
    // 0 <= x < 3, x represents the activity underetaken on the ith day
    // We will further state optimize the DP array to only store values of all x for the next day
    // Setting up the DP array (We are using Iterative DP)

    vector<int> dp(3);  // Only need to store last 3 states to calculate the latest states (Space Optimisation)
    dp = {points[n - 1][0], points[n - 1][1], points[n - 1][2]};     //Initialising the table with values for last day

    // We iterate from last day to the first day
    for(int i = n - 2; i >= 0; i--){
        // Initialize a temporary array to store the values for current day
        vector<int> temp(3);
        for(int j = 0; j < 3; j++){
            // Tranisition: dp[i][x] = points[i][x] + max(dp[i + 1][y] for all y != x)
            temp[j] = points[i][j] + max(dp[(j + 1)%3], dp[(j + 2)%3]);
        }
        // Update the values of current day into the dp table
        dp = temp;
    }

    // Output the maximum value possible
    cout << max(dp[0], max(dp[1], dp[2]));

    // Time Complexity : O(n)
    // Space Complexity : O(1)

    return 0;
}