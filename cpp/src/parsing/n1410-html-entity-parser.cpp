#include <iostream>
#include <string_view>

class Solution {
public:
    std::string entityParser(std::string text)
    {
        std::vector<std::tuple<int, int, char>> repls {};
        std::vector<std::string> candidates = { "&quot;", "&apos;", "&amp;", "&gt;", "&lt;", "&frasl;" };
        std::vector<char> candidates_index = { '"', '\'', '&', '>', '<', '/' };
        std::string result {};

        auto parse = [&](auto it) {
            auto idx = 0;
            for (auto& candidate : candidates) {
                size_t i = 0;
                while (i < candidate.size() && (it + i) != text.end()) {
                    if (*(it + i) != candidate[i]) {
                        break;
                    }

                    i++;
                }

                if (i == candidate.size()) {
                    return std::tuple((int)candidate.size(), candidates_index[idx]);
                }

                idx++;
            }

            return std::tuple(0, ' ');
        };

        auto it = text.begin();
        while (it < text.end()) {
            if (*it == '&') {
                auto [size, replaced] = parse(it);
                if (size > 0) {
                    // ! the key is not replace `text` in place, loop while modify is
                    // always gonna cause u headache.
                    result.push_back(replaced);
                    it += size;
                    continue;
                }
            }

            result.push_back(*it);
            it++;
        }

        return result;
    }
};

int main()
{
    Solution solution {};
    std::string in = "&amp; is an HTML entity but &ambassador; is not.";
    auto result = solution.entityParser(in);

    std::cout << "result is : \n"
              << result << std::endl;
}
