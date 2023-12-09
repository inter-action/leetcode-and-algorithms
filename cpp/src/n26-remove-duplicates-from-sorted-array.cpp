#include <iostream>

class Solution {
public:
  int removeDuplicates(std::vector<int> &nums) {
    auto it = nums.begin();
    auto start = it;
    auto ends = nums.end();
    // end is the last non-element position
    if (nums.size() <= 1)
      return nums.size();
    int last = *it;
    it++;
    auto removed = 0;
    for (; it != ends; it++) {
      std::cout << "it: " << *it << " last: " << last << std::endl;
      if (*it == last) {
        removed++;
        continue;
      } else {
        last = *it;
        std::iter_swap(++start, it);
      }
    }

    // return ends - begin;
    return nums.size() - removed;
  }
};

int main() {
  Solution solution{};
  std::vector<int> in = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
  std::cout << "the result is: " << solution.removeDuplicates(in) << std::endl;
  std::for_each(in.begin(), in.end(), [](int &n) { std::cout << n; });
  std::cout << std::endl;
}
