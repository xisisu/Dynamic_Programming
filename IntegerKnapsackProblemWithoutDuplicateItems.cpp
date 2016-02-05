//
// Created by Sisu on 12/15/2015.
//

/*
 * Integer Knapsack Problem (Duplicate Items Forbidden). This is the same problem as the example above, except here
 * it is forbidden to use more than one instance of each type of item.
 *
 * 0/1 knapsack
 * http://people.cs.clemson.edu/~bcdean/dp_practice/
 */

#include <iostream>
#include <vector>
#include <algorithm>

struct Item {
    int value, weight;
    Item(int v, int w) : value(v), weight(w) {}
};

class Solution {
public:
    std::vector<Item> knapsackWithoutDuplicateItems(const std::vector<Item>& items, int weightLimit) {
        // DP[i,j]: fill exactly a capacity j with subset of items 1...i
        // DP[i,j] = max{ M(i-1, j), M(i-1, j-Wi) + Vi }
        // result = max{ DP[n, j] }, where iterate all js
        if (weightLimit <= 0 || items.empty()) { return std::vector<Item>(); }
        int N = items.size();
        int dp[N+1][weightLimit+1];

        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= weightLimit; ++j) {
                if (i == 0 || j == 0) { dp[i][j] = 0; }
                else if (items[i-1].weight > j) { dp[i][j] = dp[i - 1][j]; }
                else { dp[i][j] = std::max(dp[i-1][j], dp[i-1][j-items[i-1].weight] + items[i - 1].value); }
            }
        }

        std::vector<Item> res;
        for (int i = N; i > 0; --i) {
            if (dp[i][weightLimit] != dp[i-1][weightLimit]) {
                res.push_back(Item(items[i-1]));
                weightLimit -= items[i-1].weight;
                if (weightLimit == 0) { break; }
            }
        }

        return res;
    }

    int knapsackWithoutDuplicateItems2(const std::vector<Item>& items, int weightLimit) {
        if (weightLimit <= 0 || items.empty()) { return 0; }
        int dp[weightLimit+1];
        for (int i = 0; i <= weightLimit; ++i) { dp[i] = 0; }
        for (int i = 1; i <= items.size(); ++i) {
            for (int j = weightLimit; j >= items[i-1].weight; --j) {
                int val = dp[j-items[i-1].weight] + items[i-1].value;
                dp[j] = std::max(dp[j], val);
            }
        }

        return dp[weightLimit];
    }
};

int main() {
    Solution sol;
    std::vector<std::vector<Item>> tests = {
              {} // empty
            , { Item(1, 1) } // 1 item
            , { Item(1, 1), Item(2, 3), Item(4, 5), Item(7, 8) }
    };
    std::vector<int> weightLimits = { -1, 0, 1, 10, 100};

    for (const auto& test: tests) {
        for (const auto& weightLimit: weightLimits) {
            // input
            std::cout << "input: ";
            for (const auto& item: test) {
                std::cout << "(w:" << item.weight << ", v:" << item.value << "), ";
            }
            std::cout << std::endl << "limit: " << weightLimit << std::endl << "pick: ";

            // method 1
            auto res = sol.knapsackWithoutDuplicateItems(test, weightLimit);
            int weightSum = 0, valueSum = 0;
            for (const auto& item: res) {
                std::cout << "(w:" << item.weight << ", v:" << item.value << "), ";
                weightSum += item.weight;
                valueSum  += item.value;
            }
            std::cout << std::endl << "total weight: " << weightSum << ", total value: " << valueSum << std::endl;

            // method 2
            std::cout << "method 2, total value is: " << sol.knapsackWithoutDuplicateItems2(test, weightLimit) << std::endl << std::endl;
        }
    }

    return 0;
}