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
    ListNode* reverseKGroup(ListNode* head, int k) {

      int i = 0;
      ListNode* cur = head;
      ListNode* pre_revesed_tail = nullptr;
      ListNode* rev_tail = nullptr;
      ListNode* pre = nullptr;
      ListNode* rev_cur = nullptr;
      ListNode* result_head = nullptr;
      


      while (cur) {
        i++;

        pre = cur;
        cur = cur->next;

        if (!rev_cur) {
          rev_cur = pre;
          rev_tail = rev_cur;
          pre->next = nullptr;
        } else {
          pre->next = rev_cur;
          rev_cur = pre;
        }

        if (i == k) {
          if (!result_head) {
            result_head = rev_cur;
          }

          if (pre_revesed_tail) {
            pre_revesed_tail->next = rev_cur;
          }
          pre_revesed_tail = rev_tail;
          rev_tail = nullptr;
          rev_cur = nullptr;

          i = 0;
        }
      }

      // should refactor this to a common lambda

      // return: head/tail of revsesed nodes
      // auto revserse_until = [](ListNode* head, std::fun<bool(ListNode*)>) -> std::pair<ListNode*, ListNode*> {...}

      // too lazy too do that. next time
      // revese back remaining nodes
      cur = rev_cur;
      ListNode* rev_cur_dup = nullptr;
      while (cur) {
        pre = cur;
        cur = cur->next;

        // 5 4
        if (!rev_cur_dup) {
          rev_cur_dup = pre;
          rev_cur_dup->next = nullptr;
        } else {
          pre->next = rev_cur_dup;
          rev_cur_dup = pre;
        }
      }

      
      if (pre_revesed_tail) {
        pre_revesed_tail->next = rev_cur_dup;
      }

      return result_head;
    }
};

int main()
{

    // ListNode* node = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    // std::cout << "before: " << node << std::endl;
    Solution s;
    // ListNode* result = s.reverseKGroup(node, 2);
    // // 2 1 4 3 5
    // std::cout << "after: " << result << std::endl;


    // input:  1 2 3 4 5
    // expect: 3 2 1 4 5
    ListNode* node1 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    ListNode* result = s.reverseKGroup(node1, 3);
    std::cout << "after #2: " << result << std::endl;
    return 0;
}
