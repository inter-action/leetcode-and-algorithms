/// link: https://www.geeksforgeeks.org/dsa/find-the-largest-subarray-with-0-sum/
/// date: 2026-01-10
///
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <map>
#include <ostream>
#include <vector>

int maxLength(std::vector<int>& arr)
{
    if (!arr.size())
        return 0;

    int max = 0;
    int current_presum = 0;
    std::map<int, int> first_seen { { 0, -1 } };
    for (size_t i = 0; i < arr.size(); i++) {
        current_presum += arr[i];
        if (first_seen.find(current_presum) == first_seen.end()) {
            first_seen[current_presum] = i;
        }

        auto iter = first_seen.find(current_presum);
        if (iter != first_seen.end()) {
            auto previous_idx = iter->second;
            if (iter->first == current_presum) {
                max = std::max(max, static_cast<int>(i) - previous_idx);
            }
        }
    }
    return max;
};

int main()
{
    std::vector<int> arr = { 15, -2, 2, -8, 1, 7, 10 };
    // std::vector<int> arr = { 2, -2 };
    // std::vector<int> arr = {0};
    // expected:
    // Input: arr[] = [15, -2, 2, -8, 1, 7, 10]
    // Output: 5
    // Explanation: The longest subarray with sum equals to 0 is [-2, 2, -8, 1, 7].
    std::cout << maxLength(arr) << std::endl;
    return 0;
}
