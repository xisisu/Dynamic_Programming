//
// Created by Sisu on 12/5/2015.
//

/*
 * Maximum Value Contiguous Subsequence. Given a sequence of n real numbers A(1) ... A(n), determine a contiguous
 * subsequence A(i) ... A(j) for which the sum of elements in the subsequence is maximized.
 *
 * http://people.cs.clemson.edu/~bcdean/dp_practice/
 */

#include <iostream>
#include <vector>
#include <stack>

class Solution {
public:
    int maxValue(const std::vector<int>& nums) {
        int res = 0, cur = 0; // for all negative sets and empty sets, we return 0, so init res to 0 here
        for (const auto &item : nums) {
            cur += item;
            cur = std::max(cur, 0);
            res = std::max(cur, res);
        }
        return res;
    }

    int maxValuePrint(const std::vector<int>& nums) {
        int res = 0, cur = 0, end = 0;
        for (int i = 0; i < nums.size(); ++i) {
            cur += nums[i]; cur = std::max(cur, 0);
            if (cur > res) {
                res = cur;
                end = i;
            }
        }

        // get the picked elements
        int sum = res;
        std::stack<int> pick;
        while (end >= 0 && sum != 0) {
            pick.push(nums[end]);
            sum -= nums[end];
            end--;
        }

        // print the results
        std::cout << "From index " << end+1 << ", select: ";
        while (!pick.empty()) {
            std::cout << pick.top() << " ";
            pick.pop();
        }
        std::cout << std::endl << std::endl;

        return res;
    }
};

int main() {
    Solution sol;
    std::vector<std::vector<int>> tests = {
              {}           // empty set, should return 0
            , {-1}         // all negative numberss, should return 0
            , {1, 2}       // all positive numbers, should return sum 3
            , {-1, 2, -1, 2, -1, 1, -1, 2}     // should return longest 4
            , {0, 0, -1, -2, 1, 2, 3, -1, 3}   // mixed case, return 8
    };

    for (const auto& test : tests) {
        // print the input
        std::cout << "input: ";
        for (const auto&val : test) { std::cout << val << " "; }
        std::cout << ", output: ";

        // print the result
        std::cout << sol.maxValue(test) << std::endl;
        sol.maxValuePrint(test);
    }
    return 0;
}