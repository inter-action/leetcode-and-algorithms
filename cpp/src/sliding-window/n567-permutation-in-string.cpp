#include <iostream>
#include <set>
#include <map>
#include <optional>
#include <limits.h>



class Solution {
public:
    bool checkInclusion(std::string s1, std::string s2) {
        std::map<char, int> expected{};
        std::map<char, int> window{};

        for (auto& c: s1) {
           // if (!expected.count(c)) {
           //     expected[c] = 0;
           // }
           expected[c]++;
        }


        std::string_view view{s2};

        int l = 0;
        int r = 0;

        // int start = 0;
        // int end = INT_MAX;

        int matched = 0;

        while (r < s2.size()) {
            // increase right window boundary
            auto c = view[r];
            r++;

            if (expected.count(c)) {
                window[c]++;
                if (window[c] == expected[c]) {
                    matched++;
                }
            }

            if (matched != expected.size()) {
                continue;
            }
            // just exactly matched

            while (l < r) {
                // shrink left window boundary
                auto c = view[l];
                l++;

                if (expected.count(c)) {
                    if (window[c] == expected[c]) {
                        matched--;
                    }
                    window[c]--;
                }

                // window just left valid state
                if (matched < expected.size()) {
                    // check if shrinked string length is match with expected
                    if ((r - (l - 1)) == s1.size()) {
                        return true;
                    }

                    break;
                }
            }
        }

        return false;
    }
};

int main()
{
    Solution solution {};
    std::string s1 = "ab";
    std::string s2 = "eidbaooo";
    //                01234567

    auto result = solution.checkInclusion(s1, s2);
    std::cout << "the result is: " << result << std::endl;


    s2 = "eidboaoo";
    //    01234567

    result = solution.checkInclusion(s1, s2);
    std::cout << "the result is: " << result << std::endl;
}
