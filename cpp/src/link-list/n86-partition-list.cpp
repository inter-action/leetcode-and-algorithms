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

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* partition(ListNode* head, int x)
    {
        ListNode* less = nullptr;
        ListNode* new_head = nullptr;
        ListNode* gt = nullptr;
        ListNode* gt_head = nullptr;
        ListNode* cur = head;

        while (cur) {
            if (cur->val < x) {
                if (!less) {
                    less = cur;
                    new_head = less;
                } else {
                    less->next = cur;
                    less = cur;
                }
            } else {
                if (!gt) {
                    gt = cur;
                    gt_head = cur;
                } else {
                    gt->next = cur;
                    gt = cur;
                }
            }
            cur = cur->next;
        }
        if (gt) {
            gt->next = nullptr;
        }
        if (less) {
            less->next = nullptr;
        }

        if (less) {
            less->next = gt_head;
            return new_head;
        } else {
            return gt_head;
        }
    }
};

int main()
{
    // 1 4 3 2 5 2
    // 1 2 2 4 3 5
    ListNode* node = new ListNode(1, new ListNode(4, new ListNode(3, new ListNode(2, new ListNode(5, new ListNode(2))))));
    std::cout << "before: " << node << std::endl;
    Solution s;
    ListNode* result = s.partition(node, 3);
    std::cout << "after: " << result << std::endl;
    return 0;
}
