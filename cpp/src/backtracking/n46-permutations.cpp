
#include <iostream>



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


class Solution {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<bool> visisted(nums.size(), false);
        std::vector<int> result{};
        std::vector<std::vector<int>> results{};


        std::function<void()> f = [&]()->void {
            auto idx = -1;
            for (auto i = 0; i<nums.size(); i++) {
                if (!visisted[i]) {
                    idx = i;

                    // before next level down
                    result.push_back(nums[idx]);
                    visisted[idx] = true;
                    
                    // step in next level
                    f();

                    // backtracking
                    result.pop_back();
                    visisted[idx] = false;
                }
            }
            
            // no more elements, collect result
            if (idx == -1) {
                // std::vector<int> copied = result;
                // ! no need to explicitly created a copy
                // `vector::push_back` would do copy internally
                results.push_back(result);
                return;
            }

        };

        f();

        return results;
    }
};

int main()
{
    Solution solution {};
    std::vector<int> in = {1, 2, 3};
    auto results = solution.permute(in);

    std::cout << "results.size(): " << results.size() << std::endl;
    for (auto& result: results) {
        std::cout << "the result is: " << result<< std::endl;
    }
}
