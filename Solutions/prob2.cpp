#include <bits/stdc++.h>
using namespace std;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // Setting loop for testcases
    int t;
    cin >> t;
    while(t--){
        // Taking input from judge
        int n, m;
        cin >> n >> m;
        vector<vector<int>> grid(n, vector<int> (m));
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> grid[i][j];

        // If number of cells on the path is odd, getting sum of 0 is impossible
        if((n + m + 1)&1){
            cout << "NO\n";
            continue;
        }

        // States: dp[i][j] stores the minimum and maximum path sum where,
        // 0 <= i < n, represents the current row from top
        // 0 <= j < m, represents the current column from left
        // Setting up DP arrays, here we are using 2D DP to store the values
        // Note: Space Optimisation to 1D DP is also possible, but it gets a little complicated and was thus left in favor for readability
        // For max path sum possible upto (i, j), always including the cell.
        vector<vector<int>> max_dp(n, vector<int> (m));
        // For min path sum possible upto (i, j), always including the cell.
        vector<vector<int>> min_dp(n, vector<int> (m));

        for(int i = 0; i < n; i++){
            // Transition :  dp[i][j] = grid[i][j] + max/min(dp[i - 1][j], dp[i][j - 1])
            for(int j = 0; j < m; j++){
                if((i == 0) && (j == 0)){   //Edge case for the first cell of the grid
                    max_dp[i][j] = min_dp[i][j] = grid[i][j];
                }else if(i == 0){           //Case for first cell of the column
                    max_dp[i][j] = grid[i][j] + max_dp[i][j - 1];
                    min_dp[i][j] = grid[i][j] + min_dp[i][j - 1];
                }else if(j == 0){           //Case for first cell of the row
                    max_dp[i][j] = grid[i][j] + max_dp[i - 1][j];
                    min_dp[i][j] = grid[i][j] + min_dp[i - 1][j];
                }else{
                    max_dp[i][j] = grid[i][j] + max(max_dp[i - 1][j], max_dp[i][j - 1]);
                    min_dp[i][j] = grid[i][j] + min(min_dp[i - 1][j], min_dp[i][j - 1]);
                }
            }
        }

        // Output
        // If 0 is in the range, then YES, else NO
        if((min_dp[n - 1][m - 1] > 0) || (max_dp[n - 1][m - 1] < 0)) cout << "NO\n";
        else cout << "YES\n";
    }    

    // Time Complexity : O(mn)
    // Space Complexity : O(mn) (We can achieve O(m) complexity if we implement space optimisation)

    return 0;
}