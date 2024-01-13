
#include <iostream>


// NOTES:
// the most efficient approach on leetcode is leveraging `erase` api, but it feel like cheating :(

// nums.erase(nums.begin()+i);


// the key is to swap duplicated value with unique one.
class Solution {
public:
    int removeElement(std::vector<int>& nums, int val)
    {
        auto it = nums.begin();
        auto ends = nums.end();

        if (nums.size() == 0) {
            return 0;
        }
        int removed = 0;

        while (it < ends) {
            if (*it == val) {
                ends--;
                std::iter_swap(it, ends);
                removed++;
            } else {
                it++;
            }
        }

        int result = nums.size() - removed;
        nums.resize(result);
        return result;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    auto it = vec.begin();
    auto ends = vec.end();

    while (it < ends) {
        os << *it << ", ";
        it++;
    }
    os << std::endl;
    return os;
}

int main()
{
    Solution solution {};
    //  std::vector<int> in = {3, 2, 2, 3};
    std::vector<int> in = { 1 };
    std::cout << "the result is: " << solution.removeElement(in, 1) << std::endl;
    std::cout << "the result vect " << in << std::endl;
    // expected:
    // 2, nums = [2,2,_,_]
}
