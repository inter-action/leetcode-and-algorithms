
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <vector>

// syntax is:
// reuslt : nested
// nested: string | number + '[' + nested* + ']'
// string: a-z+
// number: 0-9+

// todo: using smart pointer to replace raw pointers

class Product {
public:
    // NOTE: always declare a default implementation on Base class
    virtual ~Product() = default;
    virtual std::string ToString() const = 0;
};

class StringProduct : public Product {
public:
    StringProduct(std::string s)
        : s_(s)
    {
    }


    std::string ToString() const override
    {
        return s_;
    }


private:
    std::string s_;
};

class NestedProduct : public Product {
public:
    NestedProduct(int32_t repeat)
        : repeat_(repeat)
    {
    }

    void SetChildren(std::vector<Product*> children)
    {
        children_ = std::move(children_);
    }

    void AddChild(Product* child)
    {
        children_.push_back(child);
    }

    std::string ToString() const override
    {
        std::string out;

        for (int32_t i = 0; i < repeat_; i++) {
            for (auto child : children_) {
                out += child->ToString();
            }
        }
        return out;
    }

private:
    int32_t repeat_;
    std::vector<Product*> children_ = {};
};


class Solution {
public:
    std::string decodeString(std::string s)
    {

        std::string_view view { s };
        auto it = view.cbegin();
        auto ends = view.cend();
        auto result = Parse(it, ends);
        return result->ToString();
    }

    Product* Parse(std::string_view::iterator& it, std::string_view::iterator& ends, int32_t repeat = 1)
    {
        NestedProduct* result = new NestedProduct(repeat);

        auto match = [&](auto& it, char expected) {
            if (*it == expected) {
                it++;
                return;
            }
            throw std::runtime_error("expected not match");
        };

        while (it < ends) {
            auto c = *it;

            if (c >= '0' && c <= '9') {
                auto number = 0;
                while (true) {
                    c = *it;
                    if (c >= '0' && c <= '9' && it < ends) {
                        // convert to number
                        auto n = c - '0';
                        number = number * 10 + n;
                        it++;
                    } else {
                        break;
                    }
                }
                match(it, '[');
                auto nested = Parse(it, ends, number);
                match(it, ']');
                result->AddChild(nested);
                continue;
            }

            // A-Z not supported
            if ((c >= 'a' && c <= 'z')) {
                std::string tmp = "";
                while (true) {
                    c = *it;
                    if (c >= 'a' && c <= 'z' && it < ends) {
                        tmp += c;
                        it++;
                    } else {
                        break;
                    }
                }
                result->AddChild(new StringProduct(tmp));
                continue;
            }

            // nested case
            if (c == ']') {
                // would it increase before return ?
                // outer would match this char
                // it++;
                return result;
            }

            // todo: add string format
            throw std::runtime_error("unexpected char");
        }

        // exit from loop;
        if (it != ends) {
            throw std::runtime_error("expected EOF");
        }

        return result;
    }
};

int main()
{
    Solution solution {};
    std::string in = "3[a]2[bc]";
    // expected: aaabcbc
    auto result = solution.decodeString(in);

    std::cout << "result is : \n"
              << result << std::endl;
}
