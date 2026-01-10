/// link: https://www.geeksforgeeks.org/dsa/count-subarrays-total-distinct-elements-original-array/
/// date: 2026-01-10
/// tag: hashing, sliding window
///
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <vector>

// loop 1 at index location 0,4
// [4, 3, 4, 3, 5]
//  ^
//
//  map
//     4->2
//     3->2
//     5->1
//
// loop 2 @ 1,4
// [4, 3, 4, 3, 5]
//     ^
//
// map
//     4->1
//     3->2
//     5-1
//
// loop 3
// [4, 3, 4, 3, 5]
//        ^
//
// map
//     4->1
//     3->1
//     5->1
//
// break

int countsub(std::vector<int>& arr)
{
    if (arr.size() == 0)
        return 0;

    std::map<int, int> ele_count {};
    // count whole array by key
    for (auto i : arr) {
        auto iter = ele_count.find(i);
        if (iter == ele_count.end()) {
            ele_count[i] = 0;
        }
        ele_count[i] += 1;
    }

    auto result = 1;

    size_t l = 0;
    size_t r = arr.size() - 1;
    while (true) {
        if (l > r)
            break;

        auto le = arr[l];
        auto re = arr[r];

        if (ele_count[le] == 1 && ele_count[re] == 1) {
            break;
        }

        if (ele_count[le] != 1) {
            result += 1;
            ele_count[le] -= 1;
            l += 1;
        } else {
            result += 1;
            ele_count[re] -= 1;
            r -= 1;
        }
    }

    return result;
};

int main()
{
    // Input: arr[] = [1, 2, 1, 3]
    // Output: 2
    // Explanation: The array has 3 distinct elements. Subarrays with exactly 3 distinct elements are:
    // [1, 2, 1, 3],  [2, 1, 3]
    //
    // Input: arr[] = [4, 3, 4, 3, 5]
    // Output: 3
    // Explanation: The array has 3 distinct elements. Subarrays with exactly 3 distinct elements are:
    // [4, 3, 4, 3, 5],  [3, 4, 3, 5], [4, 3, 5]
    //
    std::vector<int> arr = { 1, 2, 1, 3 };
    // 2
    std::cout << "result: " << countsub(arr) << std::endl;
    arr = { 4, 3, 4, 3, 5 };
    // 3
    std::cout << "result: " << countsub(arr) << std::endl;
    return 0;
}
