// !! this code doesn't work, FAILED ATTEMPT!


#include <iostream>
#include <set>
#include <map>
#include <optional>
#include <limits.h>


class Solution {
public:
    std::string minWindow(std::string s, std::string t) {
        std::map<char, int> tset{};

        for (auto& c: t) {
           if (!tset.count(c)) {
               tset[c] = 0;
           }
           tset[c]++;
        }


        auto scan = [&](std::string_view view) ->std::optional<std::map<char, std::vector<int>>> {
            std::map<char, std::vector<int>> map{};
            auto it = view.cbegin();
            auto end = view.cend();

            size_t i = 0;
            while (it < end) {

                if (tset.count(*it) > 0) {

                    if (map.count(*it) == 0) {
                        map[*it] = {};
                    }

                    map[*it].push_back(i);
                }

                i++;
                it++;
            }

            if (map.size() != tset.size()) {
                return std::nullopt;
            }

            for (auto& it: tset) {
                if (map[it.first].size() < tset[it.first]) {
                    return std::nullopt;
                }
            }

            return map;
        };

        if (!s.size()) return "";
        if (!t.size()) return "";

        std::string_view view{s};

        size_t l = 0;
        size_t r = s.size();

        auto max = [](std::vector<int>& vec) {
            int m = vec[0];
            for (auto i = 1; i<vec.size(); i++) {
                if (vec[i] > m) {
                    m = vec[i];
                }
            }

            return m;
        };

        auto min = [](std::vector<int>& vec) {
            int m = vec[0];
            for (auto i = 1; i<vec.size(); i++) {
                if (vec[i] < m) {
                    m = vec[i];
                }
            }

            return m;
        };

        while(true) {
            view = view.substr(l, r);
            auto result = scan(view);
            if (!result.has_value()) {
                return "";
            }

            auto map = result.value();
            size_t min_i = INT_MAX;
            size_t max_i = 0;
            auto map_idx = 0;
            auto map_size = map.size();
            // hash map can't use <
            for (auto& map_it: map) {
                if (map_idx >= map_size) {
                    break;
                }

                auto& key = map_it.first;
                auto& second = map_it.second;

                if (second.size() > tset[key]) {
                    auto k = min(second);
                    if (k < min_i) {
                        min_i = k;
                    }
                    auto j = max(second);
                    if (j > max_i) {
                        max_i = j;
                    }
                }
                map_idx++;
            }

            if (min_i != INT_MAX && max_i != 0) {
                auto left_distance = 0;
                auto right_distance = 0;

                for (auto& map_it: map) {
                    auto& key = map_it.first;
                    auto& values = map_it.second;

                    for (auto i = 0; i<values.size(); i++) {
                        if (i == tset[key]) {
                            break;
                        }
                        left_distance += (values[i] - min_i);
                    }

                    for (auto i = 0; i<values.size(); i++) {
                        if (i == tset[key]) {
                            break;
                        }
                        right_distance += (max_i - values[values.size() - 1 - i]);
                    }
                }
                if ( left_distance > right_distance ) {
                    l = min_i + 1;
                } else {
                    r = max_i;
                }
                continue;
            }

            if (min_i != INT_MAX) {
                l = min_i + 1;
                continue;
            }

            if (max_i != 0) {
                r = max_i;
                continue;
            }

            min_i = INT_MAX;
            max_i = 0;
            for (auto& map_it: map) {
                if (map_it.second.size() == 0) continue;

                auto k = min(map_it.second);
                if (k < min_i) {
                    min_i = k;
                }
                auto j = max(map_it.second);
                if (j > max_i) {
                    max_i = j;
                }
            }
            return std::string{view.substr(min_i, max_i - min_i + 1)};
        }
        

    }
};

int main()
{
    Solution solution {};
    // std::string in = "ADOBECODEBANC";
    // std::string t = "ABC";
    std::string in = "acbbaca";
    //                   baca         cwae
    std::string t = "aba";
    auto result = solution.minWindow(in, t);
    std::cout << "the result is: " << result << std::endl;
    // expected:
    // BANC



    // in = "a";
    // t = "a";
    // result = solution.minWindow(in, t);
    // std::cout << "the result is: " << result << std::endl;
    // // expected:
    // // a

    // in = "a";
    // t = "aa";
    // result = solution.minWindow(in, t);
    // std::cout << "the result is: " << result << std::endl;
    // // expected:
    // // ""
}
