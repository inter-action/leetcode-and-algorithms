#include <iostream>

struct ListNode {
    int val;
    ListNode* next;

    ListNode()
        : val(0)
        , next(nullptr)
    {
    }

    ListNode(int x)
        : val(x)
        , next(nullptr)
    {
    }

    ListNode(int x, ListNode* next)
        : val(x)
        , next(next)
    {
    }
};

std::ostream& operator<<(std::ostream& os, ListNode* const head)
{
    const ListNode* cur = head;

    while (cur) {
        os << cur->val << " -> ";
        cur = cur->next;
    }
    return os;
}

// the official solution is clear due to it adds a dummy node to the head. so it can skip various edge case
//         ListNode* dummy = new ListNode(0, head);

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        auto cur = head;
        std::vector<ListNode*> stack {};

        while (cur != nullptr) {
            stack.push_back(cur);
            cur = cur->next;
        }

        auto i = 0;
        ListNode* target = nullptr;

        while (true) {
            auto size = stack.size();
            if (size == 0) {
                break;
            }
            ListNode* top = stack.back();
            stack.pop_back();

            if (top == nullptr) {
                break;
            }

            if (i == n - 1) {
                if (stack.size() == 0) {
                    return top->next;
                }
                target = stack.back();
                break;
            }

            i += 1;
        }

        if (target != nullptr) {
            // remove
            auto next = target->next;
            if (next) {
                target->next = next->next;
                next->next = nullptr;
                // memory leak?, adding delete ?
                // delete next;
            } else {
                target->next = nullptr;
            }

            return head;
        }

        return nullptr;
    }
};

int main()
{
    // Input: head = [1,2,3,4,5], n = 2
    // Output: [1,2,3,5]
    ListNode* node = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    std::cout << "removeNthFromEnd before: " << node << std::endl;
    Solution s;
    ListNode* result = s.removeNthFromEnd(node, 2);
    std::cout << "removeNthFromEnd after: " << result << std::endl;
    return 0;
}
