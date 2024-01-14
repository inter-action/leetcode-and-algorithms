// !! THIS code does not work.
// pls check the official solution - https://leetcode.cn/problems/longest-palindromic-substring/solutions/255195/zui-chang-hui-wen-zi-chuan-by-leetcode-solution


// 在 s 中寻找以 s[l] 和 s[r] 为中心的最长回文串
// var palindrome = function(s, l, r) {
//     // 防止索引越界
//     while (l >= 0 && r < s.length
//             && s.charAt(l) == s.charAt(r)) {
//         // 双指针，向两边展开
//         l--;
//         r++;
//     }
//     // after iteration, l & r would be out of bound, l need add one offset back, this is related to substring impl, it's 
//     // exlusive on right range.
//     // 返回以 s[l] 和 s[r] 为中心的最长回文串
//     return s.substring(l + 1, r);
// }
//
//



// the fucking lession is I should do the palindrome check using center position of the string and expand it outwards
// So it can be simplely looped from string index from 0 to s.length


// a b c d e
//     ^
//   ^   ^


// this implementation is just straight ugly. and the need to implements a custom hash function for tuple stopped me from
// continuing this shit.
// I keep it here for references usage like 
// - unordered_map
// - optional
// - tuple
// - string_view

// which I got to say, cpp containers, especially unordered_map is not that easy to use.


#include <iostream>
#include <string_view>
#include <unordered_map>


class Solution {
public:
    std::string longestPalindrome(std::string s) {
        auto is_palindrome = [](std::string_view view) -> bool {
            auto it = view.begin();
            auto ends = view.end();
            if (view.size() <= 1) return true;
            ends--;

            while (it < ends) {
                if (*it != *ends) {
                    return false;
                }
                it++;
                ends--;
            }

            return true;
        };

        if (s.size() <= 1) {
            return s;
        }

        // std::string implements a custom conversion function from string to string_view
        std::string_view view{s};

        std::unordered_map<std::tuple<size_t, size_t>, std::optional<std::string_view>> cache{};
        std::function<std::optional<std::string_view>(size_t, size_t)> f = [&](size_t start, size_t ends) -> std::optional<std::string_view> {
            if (start >= ends) {
                return std::nullopt;
            }
            std::string_view subview = view.substr(start, ends - start);

            if (auto search = cache.find(std::tuple(start, ends)); search != cache.end()) {
                return search->second;
            }

            if (is_palindrome(subview)) {
                cache[std::tuple(start, ends)] = subview;
                return subview;
            }

            auto l = f(start+1, ends);
            auto r = f(start, ends - 1);

            std::optional<std::string_view> result = std::nullopt;

            if (l.has_value() && r.has_value()) {
                result = l.value().size() > r.value().size() ? l : r;
            }

            if (l.has_value()) {
                result = l;
            }

            if (r.has_value()) {
                result = r;
            }

            cache[std::tuple(start, ends)] = result;

            return result;

        };

        auto max_view = f(0, view.size());

        if (max_view.has_value()) {
            // there's a constructor take string_view
            return std::string{max_view.value()};
        }
        return std::string{""};
    }
};


int main()
{
    Solution solution {};
    std::string s{"babaddtattarrattatddetartrateedredividerb"};
    std::cout << "the result is: " << solution.longestPalindrome(s) << std::endl;
    // expected:
    // bab

    // 
    // std::string s1{"cbbd"};
    // // expected: cbbd
    // std::cout << "the result is: " << solution.longestPalindrome(s1) << std::endl;
}

