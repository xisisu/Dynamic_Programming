//
// Created by Sisu on 12/13/2015.
//

/*
 * Box Stacking. You are given a set of n types of rectangular 3-D boxes, where the i^th box has height h(i), width
 * w(i) and depth d(i) (all real numbers). You want to create a stack of boxes which is as tall as possible, but you
 * can only stack a box on top of another box if the dimensions of the 2-D base of the lower box are each strictly
 * larger than those of the 2-D base of the higher box. Of course, you can rotate a box so that any side functions as
 * its base. It is also allowable to use multiple instances of the same type of box.
 *
 * http://people.cs.clemson.edu/~bcdean/dp_practice/
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

struct Box {
    int _height, _width, _depth;
    Box(int height, int width, int depth) : _height(height), _width(width), _depth(depth) {}

    bool operator<(const Box other) const {
        return (_width * _depth) < (other._width * other._depth); // sort in decreasing order
    }

    bool strictLessThan(const Box other) const {
        return _width < other._width && _depth < other._depth;
    }
};

class Solution {
public:
    std::vector<Box> boxStacking(const std::vector<Box>& boxes) {
        /*
         * 1. rotate the box with constrains that width < depth, so 1 box -> 3 boxes
         * 2. sort 3*N boxes in decreasing order in terms of base area
         * 3. dp[i] = max(dp[j] + box[i].height), where j < i, j.width < i.width, and j.depth < i.depth
         */
        std::vector<Box> input;
        for (const auto& val: boxes) {
            Box box1 = Box(val._height, std::min(val._width, val._depth), std::max(val._width, val._depth));
            Box box2 = Box(val._width,std::min(val._height, val._depth), std::max(val._height, val._depth));
            Box box3 = Box(val._depth,std::min(val._height, val._width), std::max(val._height, val._width));
            input.push_back(box1);
            input.push_back(box2);
            input.push_back(box3);
        }
        std::sort(input.begin(), input.end());

        int N = input.size();
        int dp[N];
        for (int i = 0; i < N; ++i) { dp[i] = input[i]._height; } // init to the height of itself

        for (int i = 0; i < N; ++i) {
            int cur = 0;
            for (int j = 0; j < i; ++j) {
                if (input[j].strictLessThan(input[i])) {
                    cur = std::max(cur, dp[j]);
                }
            }
            dp[i] = cur + input[i]._height;
        }

        int height = 0, idx = 0;
        for (int i = 0; i < N; ++i) {
            if (dp[i] > height) {
                height = dp[i];
                idx = i;
            }
        }

        std::vector<Box> res;
        while (height > 0) {
            res.push_back(input[idx]);
            height -= input[idx]._height;
            for (int i = 0; i < idx; ++i) {
                if (input[i].strictLessThan(input[idx]) && dp[i] == height) {
                    idx = i; break;
                }
            }
        }

        std::reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    Solution sol;
    std::vector<Box> boxes = {{1,2,3}, {2,3,4}, {3,4,5}, {5,6,7}};
    std::cout << "input: ";
    for (const auto& box : boxes) {
        std::cout << "(h:" << box._height << ",w:" << box._width << ",d:" << box._depth << "), ";
    }
    std::cout << std::endl;

    auto res = sol.boxStacking(boxes);
    std::cout << "stack: ";
    for (const auto& box : res) {
        std::cout << "(h:" << box._height << ",w:" << box._width << ",d:" << box._depth << "), ";
    }
    std::cout << std::endl;

    return 0;
}