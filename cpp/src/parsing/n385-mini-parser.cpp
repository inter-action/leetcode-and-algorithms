#include <cstdlib>
#include <iostream>
#include <string_view>

class NestedInteger;

// support move / copy
class NestedInteger {
public:
    // Constructor initializes an empty nested list.
    NestedInteger();

    // Constructor initializes a single integer.
    NestedInteger(int value);

    NestedInteger(const NestedInteger&) = default;
    NestedInteger& operator=(const NestedInteger&) = default;

    NestedInteger(NestedInteger&&) = default;
    NestedInteger& operator=(NestedInteger&&) = default;

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Set this NestedInteger to hold a single integer.
    void setInteger(int value);

    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(const NestedInteger& ni);

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const std::vector<NestedInteger>& getList() const;

private:
    std::vector<NestedInteger> lists_;
    bool is_integer_ = false;
    int value_ = 0;
};

NestedInteger::NestedInteger()
{
    lists_ = {};
}

NestedInteger::NestedInteger(int value)
{
    value_ = value;
    is_integer_ = true;
}

bool NestedInteger::isInteger() const
{
    return is_integer_;
}

int NestedInteger::getInteger() const
{
    return value_;
}

void NestedInteger::add(const NestedInteger& ni)
{
    if (is_integer_) {
        is_integer_ = false;
        lists_ = {};
        lists_.push_back(NestedInteger(value_));
        value_ = 0;
    }

    lists_.push_back(ni);
}

const std::vector<NestedInteger>& NestedInteger::getList() const
{
    return lists_;
}

std::ostream& operator<<(std::ostream& os, const NestedInteger& in)
{

    std::function<void(const NestedInteger&)> to_string = [&](const NestedInteger& k) {
        if (k.isInteger()) {
            std::cout << k.getInteger();
        } else {
            std::cout << '[';
            for (auto& item : k.getList()) {
                to_string(item);
                std::cout << ',';
            }
            std::cout << ']';
        }
    };

    to_string(in);
    os << std::endl;
    return os;
}

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

// support no copy/move semantics
class TokenStream {
public:
    TokenStream(std::string_view& s)
        : s_(s)
    {
        it_ = s_.cbegin();
        end_ = s_.cend();
    }

    enum class TokenType {
        NUMBER,
        OPEN_BRACKET,
        END_BRACKET,
        // end of string
        EOD_S,
    };

    std::tuple<TokenType, std::variant<char, int>> Peek() {
        throw std::runtime_error("unimplemented");
    }

    std::tuple<TokenType, std::variant<char, int>> NextToken()
    {

        auto is_num = [](auto c){
            return c >= '0' && c <= '9';
        };

        while (it_ < end_) {
            if (*it_ == '[') {
                it_++;
                return std::tuple(TokenType::OPEN_BRACKET, '[');
            }

            if (*it_ == ']'){
                it_++;
                return std::tuple(TokenType::END_BRACKET, ']');
            }

            if (is_num(*it_) || (*it_ == '-' && is_num(*(it_+1)))) {
                int nums = 0;
                bool is_neg = false;
                if (*it_ == '-') {
                    is_neg = true;
                    it_++;
                }
                while (*it_ >= '0' && *it_ <= '9') {
                    nums = nums * 10 + (*it_ - '0');
                    it_++;
                }
                return std::tuple(TokenType::NUMBER, is_neg ? -nums : nums);
            }

            // ignore everything else
            it_++;
        }

        return std::tuple(TokenType::EOD_S, 'X');
    }

private:
    const std::string_view& s_;
    std::string_view::iterator it_;
    std::string_view::iterator end_;
};

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    NestedInteger deserialize(std::string s)
    {
        std::string_view in { s };
        TokenStream ts(in);

        auto result = Parse(ts);
        if (!result.has_value()) {
            throw std::runtime_error("failed to parse");
        }

        return std::move(result.value());
    }

    std::optional<NestedInteger> Parse(TokenStream& ts)
    {
        std::optional<NestedInteger> result = std::nullopt;

        while (true) {
            auto [ttype, variant] = ts.NextToken();
            if (ttype == TokenStream::TokenType::EOD_S) {
                break;
            }

            if (ttype == TokenStream::TokenType::OPEN_BRACKET) {
                NestedInteger list = ParseList(ts);

                if (!result.has_value()) {
                    result = list;
                } else if (result->isInteger()) {
                    throw std::runtime_error("an list type is expected");
                } else {
                    result->add(list);
                }

                continue;
            }

            if (ttype == TokenStream::TokenType::NUMBER) {
                NestedInteger number { std::get<int>(variant) };
                if (!result.has_value()) {
                    result = number;
                } else if (result->isInteger()) {
                    throw std::runtime_error("an list type is expected");
                } else {
                    result->add(number);
                }

                continue;
            }

            throw std::runtime_error("unexpected ttype");
        }

        return result;
    }

    NestedInteger ParseList(TokenStream& ts)
    {
        NestedInteger list {};

        std::tuple<TokenStream::TokenType, std::variant<char, int>> tuple;
        while (true) {
            tuple = ts.NextToken();
            auto [ttype, variant] = tuple;

            if (ttype == TokenStream::TokenType::EOD_S) {
                break;
            }

            if (ttype == TokenStream::TokenType::OPEN_BRACKET) {
                list.add(ParseList(ts));
                continue;
            }

            if (ttype == TokenStream::TokenType::NUMBER) {
                NestedInteger number { std::get<int>(variant) };
                list.add(number);
                continue;
            }

            break;
        }

        if (std::get<0>(tuple) != TokenStream::TokenType::END_BRACKET) {
            throw std::runtime_error("end bracket expected");
        }

        return list;
    }
};

int main()
{
    Solution solution {};
    // 324
    std::string in = "-1";
    auto result = solution.deserialize(in);

    std::cout << "result is : \n" << result << std::endl;
}
