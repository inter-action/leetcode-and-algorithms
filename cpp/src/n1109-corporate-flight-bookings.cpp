
#include <iostream>

// 差分数组的应用

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
    std::vector<int> corpFlightBookings(std::vector<std::vector<int>>& bookings, int n) {
        std::vector<int> out(n);

        if (!bookings.size()) return out;

        for (auto& record: bookings) {
            if (record.size() != 3) continue;

            auto start_index = record[0] - 1;
            auto end_index = record[1] - 1;
            auto seats = record[2];

            // 差分数组记账
            out[start_index] += seats;
            if ((end_index + 1) < n) {
                out[end_index + 1] -= seats;
            }
        }

        // reverse 差分数组
        for (auto i = 1; i < out.size(); i++) {
            out[i] = out[i-1] + out[i];
        }

        return out;
    }
};


int main()
{
    Solution solution {};
    std::vector<std::vector<int>> in = {{ 1,2,10 },{ 2,3,20 },{ 2,5,25 }};
    std::cout << "the result is: " << solution.corpFlightBookings(in, 5) << std::endl;
    // expected:
    // [10,55,45,25,25]
}
