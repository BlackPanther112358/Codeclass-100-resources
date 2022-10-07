#include <bits/stdc++.h>
using namespace std;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // Taking input from judge
    int n, q;
    cin >> n;
    vector<int> vol(n);
    for(int i = 0; i < n; i++) cin >> vol[i];

    // Making a prefix sum array
    vector<long long int> prefix(n);
    prefix[0] = vol[0];
    for(int i = 1; i < n; i++) prefix[i] = vol[i] + prefix[i - 1];

    // States: dp[i] represents time taken to fill i + 1 locks with i + 1 pipes open, 0 <= i < n
    // NOTICE that dp[i] is for first i + 1 locks/pipes, not i.
    // Making the DP table
    vector<long long int> dp(n);
    // Base case as only one pipe is open
    dp[0] = vol[0];
    // Transition: dp[i + 1] = ceil(prefix[i + 1]/i), as to fill first i pipes are open and we have to fill prefix[i + 1] volume
    // But the first i - 1 locks may take more time as ith pipe is not helping them, thus also include time to fill them;
    for(int i = 1; i < n; i++) dp[i] = max(dp[i - 1], (prefix[i] + i)/(i + 1));

    // Taking input for queries
    cin >> q;
    while(q--){
        int t;
        cin >> t;

        // Binary search the number of pipes to open
        int low = 1, high = n, ans = -1;
        while(low <= high){
            int mid = low + (high - low)/2;
            // To find the time to fill all the locks with mid pipes open, here we also consider the time to fill first mid locks also.
            long long int time = max(dp[mid - 1], (prefix[n - 1] + mid - 1)/mid);
            if(time <= t){
                ans = mid;
                high = mid - 1;
            }else{
                low = mid + 1;
            }
        }
        cout << ans << "\n";
    }    

    // Time Complexity : O(n + q*log(n))
    // Space Complexity : O(n)

    return 0;
}