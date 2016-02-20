//
// Created by Sisu on 2/20/2016.
//

/*
 * Optimal Strategy for a Game. Consider a row of n coins of values v(1) ... v(n), where n is even. We play a game
 * against an opponent by alternating turns. In each turn, a player selects either the first or last coin from the row,
 * removes it from the row permanently, and receives the value of the coin. Determine the maximum possible amount of
 * money we can definitely win if we move first.
 */

#include <vector>
#include <iostream>

class Solution {
public:
    std::vector<int> optimalStrategyForGame(const std::vector<int>& input) {
        /*
         * V[i][j] = max{ A[i] + min{V[i+1][j-1],V[i+2][j]}, A[j] + min{V[i][j-2],V[i+1][j-1]} }
         */
        std::vector<int> result;
        if (input.empty()) { return result; }
        if (input.size() % 2 != 0) {
            std::cout << "Invalid input size " << input.size() << ", must be even." << std::endl;
            return result;
        }

        int N = input.size();
        int DP[N][N];

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                DP[i][j] = 0;
            }
        }

        for (int len = 0; len < N; ++len) {
            for (int i = 0; i < N-len; ++i) {
                if (len == 0) { DP[i][i+len] = input[i]; }
                else if (len == 1) { DP[i][i+len] = std::max(input[i], input[i+len]); }
                else {
                    int j = i+len;
                    int val_1 = input[i] + std::min(DP[i+1][j-1], DP[i+2][j]);
                    int val_2 = input[j] + std::min(DP[i+1][j-1], DP[i][j-2]);
                    DP[i][j] = std::max(val_1, val_2);
                }
            }
        }

        // now we track our steps
        int s = 0, e = N-1;
        while (s < e) {
            if (DP[s][e] == input[s] + std::min(DP[s+1][e-1], DP[s+2][e])) {
                result.push_back(input[s]);
                if (DP[s+1][e-1] > DP[s+2][e]) {
                    s += 2;
                } else {
                    s += 1; e -= 1;
                }
            } else { // DP[s][e] == input[e] + std::min(DP[s+1][e-1], DP[s][e-2]
                result.push_back(input[e]);
                if (DP[s+1][e-1] > DP[s][e-2]) {
                    e -= 2;
                } else {
                    s += 1; e -= 1;
                }
            }
        }

        return result;
    }
};

int main() {
    std::vector<std::vector<int>> tests = {
            {}
            , {100, 101}
            , {99, 100}
            , {100, 100}
            , {1,2,3,4}
            , {4,3,2,1}
            , {1,2,3,4,5,6,7,8,9,10}
            , {10,9,8,7,6,5,4,3,2,1}
            , {1,43,57,43,23,56,8, 3,3,6,89,3}
    };
    Solution sol;

    for (auto const& test : tests) {
        std::cout << "test: ";
        for (auto const& item : test) {
            std::cout << item << ", ";
        }
        auto pick = sol.optimalStrategyForGame(test);
        std::cout << "pick: ";
        auto sum = 0;
        for (auto const& item : pick) {
            std::cout << item << ", ";
            sum += item;
        }
        std::cout << "sum: " << sum << std::endl;
    }

    return 0;
}