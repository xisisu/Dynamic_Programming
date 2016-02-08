//
// Created by Sisu on 2/7/2016.
//

/*
 * Given two text strings A of length n and B of length m, you want to transform A into B with a minimum number of
 * operations of the following types: delete a character from A, insert a character into A, or change some character
 * in A into a new character. The minimal number of such operations required to transform A into B is called the edit
 * distance between A and B.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    int editDistance(const std::string& a, const std::string& b) {
        /*
         * DP[i][j]: result to edit from a[i] to b[j]
         */
        int N = a.size(), M = b.size();
        int DP[N+1][M+1];

        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= M; ++j) {
                if (i == 0 || j == 0) { DP[i][j] = std::max(i, j); }
                else { DP[i][j] = std::min( std::min(DP[i-1][j], DP[i][j-1])+1, DP[i-1][j-1]+(a[i-1] != b[j-1]) ); }
            }
        }

        return DP[N][M];
    }
};

int main() {
    Solution sol;
    std::vector<std::pair<std::string, std::string>> tests = {
            std::make_pair("", "") // both are empty
            , std::make_pair("", "a") // 1 empty
            , std::make_pair("a", "a") // same
            , std::make_pair("a", "aaaaa") // same character
            , std::make_pair("a", "b")  // same length, diff character
            , std::make_pair("b", "abc") // diff length
            , std::make_pair("abc", "def")
            , std::make_pair("a", "bcdefghijklmn")
    };

    for (auto const& test : tests) {
        // print input
        std::cout << "input: " << test.first << "(" << test.first.length() << "), " \
                                << test.second << "(" << test.second.length() << ")" << std::endl;
        std::cout << "result: " << sol.editDistance(test.first, test.second) << std::endl << std::endl;
    }

    return 0;
}