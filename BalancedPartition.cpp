//
// Created by Sisu on 2/7/2016.
//

/*
 * You have a set of n integers each in the range 0 ... K. Partition these integers into two subsets such that you
 * minimize |S1 - S2|, where S1 and S2 denote the sums of the elements in each of the two subsets.
 */

#include <iostream>
#include <vector>
#include <set>
#include <iomanip>

class Solution {
public:
    void balancedPartition(const std::vector<int>& input, std::vector<int>& res1, std::vector<int>& res2) {
        /*
         * DP[i][j] = 1 if some subset of A[1-i] have a sum of j
         * DP[i][j] = 1 if DP[i-1][j] = 1 or DP[i-1][j-Ai] = 1
         * DP[i][j] = max{ DP[i-1][j], DP[i-1][j-Ai] }
         */
        if (input.empty()) { return; }
        int S = 0, N = input.size();
        for (auto const& item : input) { S += item; }

        int DP[N+1][S+1];
        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= S; ++j) {
                if (i == 0 || j == 0) { DP[i][j] = 0; }
                else if (input[i-1] > j) { DP[i][j] = DP[i-1][j]; }
                else if (input[i-1] == j) { DP[i][j] = 1; }
                else { DP[i][j] = DP[i-1][j] || DP[i-1][j-input[i-1]]; }
            }
        }

        // get the result
        int C = S / 2, dist = 0;
        while (dist < C) {
            if (DP[N][C-dist] == 1) { break; }
            ++dist;
        }
        C -= dist;

        std::set<int> res1Items; // we use an set to store indexes for items in S1, due to duplicate items in input
        int i = N;
        while (i > 0) {
            if (DP[i][C] != DP[i-1][C]) {
                res1Items.insert(i-1);
                C -= input[i-1];
            }
            --i;
        }

        res1.clear();
        res2.clear();
        for (int j = 0; j < N; ++j) {
            if (res1Items.count(j)) { res1.push_back(input[j]); }
            else { res2.push_back(input[j]); }
        }
    }
};

int main() {
    Solution sol;
    std::vector<std::vector<int>> tests = {
            { } // empty sets
            , {1} // single item
            , {1, 100} // two items
            , {1,2,3,4} // sum[res1] == sum[res2]
            , {1,2,3,4,5} // sum[res1] != sum[res2], off by 1
            , {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} // all same items
            , {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} // all same items
            , {1,2,3,4,5,6,7,8,9,10,100} // unbalanced partition
    };

    for (auto const& test : tests) {
        // print input
        int sum = 0;
        std::cout << "input: ";
        for (auto const& item : test) {
            std::cout << item << ", ";
            sum += item;
        }
        std::cout << ". Sum: " << sum << std::endl;

        std::vector<int> res1, res2;
        sol.balancedPartition(test, res1, res2);

        // print output
        std::cout << "res1: ";
        sum = 0;
        for (auto const& item : res1) {
            std::cout << item << ", ";
            sum += item;
        }
        std::cout << ". Sum: " << sum << std::endl;
        std::cout << "res2: ";
        sum = 0;
        for (auto const& item : res2) {
            std::cout << item << ", ";
            sum += item;
        }
        std::cout << ". Sum: " << sum << std::endl << std::endl;
    }

    return 0;
}