//
// Created by Sisu on 2/20/2016.
//

/*
 * Car Assembly (see Figure 15.1 in CLRS): A factory has two assembly lines, each with n stations.A station is denoted
 * by Si;j where i is either 1 or 2 and indicates the assembly line the station is on, and j indicates the number of
 * the station. The time taken per station is denoted by ai;j . A car chasis must pass through each of the n stations
 * in order before exiting the factory. After it passes through station Si;j it will continue to station Si;j+1 unless
 * it decides to transfer to the other line. Continuing on the same line incurs no extra cost, but transfering from
 * line i at station j 􀀀 1 to station j on the other line takes time ti;j . There is also an entry time ei and exi
 * t time xi which may be dierent for the two lines. Give an algorithm for computing the minimum time it will take to
 * build a car chasis.
 */

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> carAssembly(const std::vector<int>& a, const std::vector<int>& b, const std::vector<int>& t) {
        /*
         * dp1[i] = a[i-1] + min{ dp1[i-1], dp2[i-1]+t[i] }
         * dp2[i] = b[i-1] + min{ dp2[i-1], dp1[i-1]+t[i] }
         */
        if (a.size() != b.size() || a.size() != t.size()) {
            std::cout << "Invalid input" << std::endl;
            return std::vector<int>();
        }
        if (a.empty()) {
            return std::vector<int>();
        }

        int N = a.size();
        int dp[2][N];

        for (int i = 0; i < N; ++i) {
            if (i == 0) {
                dp[0][i] = a[i];
                dp[1][i] = b[i];
            } else {
                dp[0][i] = a[i] + std::min(dp[0][i-1], dp[1][i-1] + t[i]);
                dp[1][i] = b[i] + std::min(dp[1][i-1], dp[0][i-1] + t[i]);
            }
        }

        // construct the path
        std::vector<int> result;
        int which = dp[0][N-1] < dp[1][N-1] ? 0 : 1;
        for (int i = N-1; i >= 0; --i) {
            int val = which == 0 ? a[i] : b[i];
            result.push_back(val);

            if (i == 0) { break; }

            if (which == 0 && dp[0][i] != (a[i] + dp[0][i-1])) { which = 1; }
            else if (which == 1 && dp[1][i] != (b[i] + dp[1][i-1])) { which = 0; }
        }

        // note the returned result does not track the transit cost
        std::reverse(result.begin(), result.end());
        return result;
    }
};

int main() {
    Solution sol;
    std::vector<int> a = {1,8,1,8,1,8,1};
    std::vector<int> b = {8,1,8,1,8,1,8};
    std::vector<int> t = {1,1,1,1,1,1,1};

    std::cout << "input: " << std::endl;
    std::cout << "  a: ";
    for (auto const& item : a) {
        std::cout << item << ", ";
    }
    std::cout << std::endl << "  b: ";
    for (auto const& item : b) {
        std::cout << item << ", ";
    }
    std::cout << std::endl << "  t: ";
    for (auto const& item : t) {
        std::cout << item << ", ";
    }

    std::cout << std::endl << "res: ";
    for (auto const& item: sol.carAssembly(a, b, t)) {
        std::cout << item << ", ";
    }
    std::cout << std::endl;

    return 0;
}