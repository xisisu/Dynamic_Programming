//
// Created by Sisu on 2/7/2016.
//

/*
 * You are given a boolean expression consisting of a string of the symbols 'true', 'false', 'and', 'or', and 'xor'.
 * Count the number of ways to parenthesize the expression such that it will evaluate to true. For example, there are
 * 2 ways to parenthesize 'true and false xor true' such that it evaluates to true.
 */

#include <iostream>
#include <vector>
#include <string.h> // for memset

class Solution {
public:
    int countingBooleanParenthesizations(const std::string& input) {
        /*
         * T_val[i][j]: from i to j, ways to make it true
         */
        if (input.empty()) { return 0; }

        int N = input.size()/2;
        int T_val[N+1][N+1];
        int F_val[N+1][N+1];
        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= N; ++j) {
                T_val[i][j] = 0;
                F_val[i][j] = 0;
            }
        }

        for (int i = 0; i <= N; ++i) {
            if (input[2*i] == '1') { T_val[i][i] = 1; }
            else { F_val[i][i] = 1; }
        }

        for (int len = 1; len <= N; ++len) {
            for (int i = 0; i <= N-len; ++i) {
                for (int j = i; j < i+len; ++j) {
                    switch (input[2*j+1]) {
                        case '&':
                            T_val[i][i+len] += T_val[i][j] * T_val[j+1][i+len];

                            F_val[i][i+len] += F_val[i][j] * F_val[j+1][i+len];
                            F_val[i][i+len] += T_val[i][j] * F_val[j+1][i+len];
                            F_val[i][i+len] += F_val[i][j] * T_val[j+1][i+len];
                            break;
                        case '|':
                            T_val[i][i+len] += T_val[i][j] * T_val[j+1][i+len];
                            T_val[i][i+len] += T_val[i][j] * F_val[j+1][i+len];
                            T_val[i][i+len] += F_val[i][j] * T_val[j+1][i+len];

                            F_val[i][i+len] += F_val[i][j] * F_val[j+1][i+len];
                            break;
                        default:
                            std::cout << "Invalid input: " << input << std::endl;
                            return 0;
                    }
                }
            }
        }

        return T_val[0][N];
    }
};

int main() {
    Solution sol;
    std::vector<std::string> tests = {
             "" // empty
             , "1"
             , "0"
             , "1&0"
             , "1&1&1"
             , "0&0&0&0&0"
             , "1&1&1&1&1"
             , "1&1&1&1&1&0&1"
             , "1|0"
             , "0|0|0|0|0"
             , "1|1|1|1|1"
             , "0|0|0|0|0|1|0"
             , "1&0|0|0|1"
    };

    for (auto const& test : tests) {
        std::cout << "input: " << test << ", res: " << sol.countingBooleanParenthesizations(test) << std::endl;
    }

    return 0;
}