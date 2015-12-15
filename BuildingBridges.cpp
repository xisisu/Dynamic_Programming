//
// Created by Sisu on 12/14/2015.
//

/*
 * Building Bridges. Consider a 2-D map with a horizontal river passing through its center. There are n cities on the
 * southern bank with x-coordinates a(1) ... a(n) and n cities on the northern bank with x-coordinates b(1) ... b(n).
 * You want to connect as many north-south pairs of cities as possible with bridges such that no two bridges cross.
 * When connecting cities, you can only connect city i on the northern bank to city i on the southern bank. (Note:
 * this problem was incorrectly stated on the paper copies of the handout given in recitation.)
 *
 * http://people.cs.clemson.edu/~bcdean/dp_practice/
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

class Solution {
public:
    std::vector<int> buildingBridges(const std::vector<int>& a, const std::vector<int>& b) {
        /*
         * convert to find longestIncreasingSubsequence problem
         */

        // some sanity check
        if (a.size() != b.size() || a.empty()) { return std::vector<int>(); }

        std::map<int, int> reverse_a;
        for (int i = 0; i < a.size(); ++i) { reverse_a[a[i]] = i; }

        std::vector<int> c;
        for (int i = 0; i < b.size(); ++i) {
            if (!reverse_a.count(b[i])) { return std::vector<int>(); }
            c.push_back(reverse_a[b[i]]);
        }

        // now find the longest increasing subsequence in c
        int N = c.size();
        int dp[N];
        for (int i = 0; i < N; ++i) { dp[i] = 1; } // min len should be 1

        for (int i = 0; i < N; ++i) {
            int cur = 1;
            for (int j = 0; j < i; ++j) {
                if (c[j] > c[i]) { continue; }
                cur = std::max(cur, dp[j] + 1); // can also use a track array to track which element to pick
            }
            dp[i] = cur;
        }

        int end = dp[0], idx = 0;
        for (int i = 1; i < N; ++i) {
            if (dp[i] > end) { end = dp[i]; idx = i; }
        }

        std::vector<int> idx_res;
        while (idx >= 0) {
            idx_res.push_back(c[idx]);
            int cur = 0;
            while (cur < idx) {
                if (dp[cur] == dp[idx]-1 && c[cur] <= c[idx]) {
                    break;
                }
                ++cur;
            }
            if (cur == idx) { break; }
            idx = cur;
        }

        std::reverse(idx_res.begin(), idx_res.end());

        std::vector<int> res;
        for (auto const val : idx_res) {
            res.push_back(a[val]);
        }
        return res;
    }
};

int main() {
    Solution sol;
    std::vector<std::vector<int>> tests = {
              {}      // empty
            , {1}     // single bridge
            , {11,12,13,14,15,16,17,18,19,20}    // max
    };

    std::srand(0);
    for (auto const& test : tests) {
        std::vector<int> a = test;
        std::random_shuffle(a.begin(), a.end());
        std::vector<int> b = test;
        std::random_shuffle(b.begin(), b.end());

        std::cout << "input: " << std::endl << "a: ";
        for (auto const val : a) { std::cout << val << " "; }
        std::cout << std::endl << "b: ";
        for (auto const val : b) { std::cout << val << " "; }
        std::cout << std::endl;

        auto res = sol.buildingBridges(a, b);
        std::cout << "connect: ";
        for (auto const val : res) { std::cout << val << " "; }
        std::cout << std::endl;
    }

    return 0;
}