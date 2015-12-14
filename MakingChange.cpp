//
// Created by Sisu on 12/13/2015.
//

/*
 * Making Change. You are given n types of coin denominations of values v(1) < v(2) < ... < v(n) (all integers).
 * Assume v(1) = 1, so you can always make change for any amount of money C. Give an algorithm which makes change
 * for an amount of money C with as few coins as possible. [on problem set 4]
 *
 * http://people.cs.clemson.edu/~bcdean/dp_practice/
 */

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

class Solution {
public:
    // we assume that all corins value are positive
    std::vector<int> makingChange(const std::vector<int>& coins, int amount) {
        // dp[amount] = min(dp[amount-coins[i]] + 1)
        if (amount <= 0 || coins.size() == 0) { return std::vector<int>(); }
        int32_t dp[amount+1];
        for (int i = 0; i <= amount; ++i) { dp[i] = INT32_MAX; }

        for (int i = 1; i <= amount; ++i) {
            for (auto val: coins) {
                if (val == i) { dp[i] = 1; }    // use this coin
                else if (val > i) { break; }  // coin is larger than current i, break (coin is sorted)
                else { dp[i] = std::min(dp[i], dp[i-val] + 1); } // can also use a track array here to keep record
            }
        }

        if (dp[amount] == INT32_MAX) { return std::vector<int>(); } // cannot find it, invalid input

        std::vector<int> res;
        auto reverse_coins = coins;
        std::reverse(reverse_coins.begin(), reverse_coins.end()); // use a reverse coin to search from big to small
        while (amount > 0) {
            int cur = INT32_MAX;
            for (auto val : reverse_coins) {
                if (val > amount) { continue; } // continue with smaller value here!
                else if (val == amount) { cur = val; break; }
                else if (dp[amount-val] == dp[amount]-1) { cur = val; break; }
            }
            amount -= cur;
            res.push_back(cur);
        }
        return res;
    }
};

int main() {
    Solution sol;
    std::vector<int> coins = {1, 2, 5, 10};
    std::vector<int> tests;
    for (int i = -1; i <= 100; ++i) tests.push_back(i);
    for (auto val : tests) {
        auto res = sol.makingChange(coins, val);
        std::cout << "input: " << val << ", size: " << res.size() << ", select: ";
        for (auto v : res) { std::cout << v << " "; }
        std::cout << std::endl;
    }

    return 0;
}