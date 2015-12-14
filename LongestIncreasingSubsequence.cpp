//
// Created by Sisu on 12/13/2015.
//

/*
 * Longest Increasing Subsequence. Given a sequence of n real numbers A(1) ... A(n), determine a subsequence
 * (not necessarily contiguous) of maximum length in which the values in the subsequence form a strictly increasing
 * sequence. [on problem set 4]
 *
 * http://people.cs.clemson.edu/~bcdean/dp_practice/
 */

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> longestIncreasingSubsequence(const std::vector<int>& nums) {
        // dp[i] = max(dp[j] + 1), where j < i and nums[j] <= nums[i]
        if (nums.size() == 0) { return std::vector<int>(); }
        int N = nums.size();
        int dp[N];
        for (int i = 0; i < N; ++i) { dp[i] = 1; } // min len should be 1

        for (int i = 0; i < N; ++i) {
            int cur = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] > nums[i]) { continue; }
                cur = std::max(cur, dp[j] + 1); // can also use a track array to track which element to pick
            }
            dp[i] = cur;
        }

        int end = dp[0], idx = 0;
        for (int i = 1; i < N; ++i) {
            if (dp[i] > end) { end = dp[i]; idx = i; }
        }

        std::vector<int> res;
        while (idx >= 0) {
            res.push_back(nums[idx]);
            int cur = 0;
            while (cur < idx) {
                if (dp[cur] == dp[idx]-1 && nums[cur] <= nums[idx]) {
                    break;
                }
                ++cur;
            }
            if (cur == idx) { break; }
            idx = cur;
        }

        std::reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    Solution sol;
    std::vector<std::vector<int>> tests = {
              {} // empty set
            , {1} // single set
            , {1,1,1,1,1,1,1,1} // all equal
            , {1,2,3,4,5} // increasing
            , {5,4,3,2,1} // decreasing
            , {3,2,5,5,6,78,9,53,2,43,45,56,7,4,1,2,2,43,54,5,6,7,4,3,2,21} // mix
    };

    for (const auto& test: tests) {
        std::cout << "input: ";
        for (auto val : test) { std::cout << val << " "; }
        auto res = sol.longestIncreasingSubsequence(test);
        std::cout << ", size: " << res.size() << ", select: ";
        for (auto val : res) { std::cout << val << " "; }
        std::cout << std::endl;
    }

    return 0;
}
